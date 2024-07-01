#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry;
    uint32_t e_phoff;
    uint32_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} Elf32_Ehdr;

// defines
typedef struct {
    uint32_t p_type;
    uint32_t p_offset;
    uint32_t p_vaddr;
    uint32_t p_paddr;
    uint32_t p_filesz;
    uint32_t p_memsz;
    uint32_t p_flags;
    uint32_t p_align;
} Elf32_Phdr;

void load_elf(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open ELF file");
        exit(EXIT_FAILURE);
    }

    // reads
    Elf32_Ehdr elf_header;
    fread(&elf_header, 1, sizeof(Elf32_Ehdr), file);

    // Validate ELF header
    if (memcmp(elf_header.e_ident, "\x7F""ELF", 4) != 0) {
        fprintf(stderr, "Not a valid ELF file\n");
        exit(EXIT_FAILURE);
    }
    if (elf_header.e_type != 2) {
        fprintf(stderr, "Not an executable file\n");
        exit(EXIT_FAILURE);
    }
    if (elf_header.e_machine != 243) {
        fprintf(stderr, "Not a RISC-V file\n");
        exit(EXIT_FAILURE);
    }
    if (elf_header.e_ident[4] != 1) {
        fprintf(stderr, "Not a 32-bit file\n");
        exit(EXIT_FAILURE);
    }

    // reads headers
    fseek(file, elf_header.e_phoff, SEEK_SET);
    for (int i = 0; i < elf_header.e_phnum; i++) {
        Elf32_Phdr prog_header;
        fread(&prog_header, 1, sizeof(Elf32_Phdr), file);

        if (prog_header.p_type == 1) {  // PT_LOAD
            fseek(file, prog_header.p_offset, SEEK_SET);
            void *segment = malloc(prog_header.p_memsz);
            fread(segment, 1, prog_header.p_filesz, file);
            memset(segment + prog_header.p_filesz, 0, prog_header.p_memsz - prog_header.p_filesz);
            printf("Loaded segment at virtual address 0x%08x\n", prog_header.p_vaddr);
            free(segment);
        }
    }

    printf("Entry point: 0x%08x\n", elf_header.e_entry);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <elf-file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    load_elf(argv[1]);
    return EXIT_SUCCESS;
}
