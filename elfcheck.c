#include <err.h>
#include <fcntl.h>
#include <libelf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <unistd.h>

int main(int argc, char **argv)
{
int fd;
Elf *e;
Elf_Kind ek;
char *name;

if(argc != 2) {
errx(EX_USAGE, "usage: %s file-name", argv[0]);
}

if(elf_version(EV_CURRENT) == EV_NONE) {
errx(EX_SOFTWARE, "ELF library initialization failed: %s", elf_errmsg(-1));
}


name = argv[1];
if((fd = open(name, O_RDONLY, 0)) < 0) {
err(EX_NOINPUT, "open \"%s\" failed", name);
}

if( (e = elf_begin(fd, ELF_C_READ, NULL)) == NULL) {
errx(EX_SOFTWARE, "elf_begin() failed: %s.", elf_errmsg(-1));
}

ek = elf_kind(e);

switch(ek) {
case ELF_K_ELF:
	printf("%s: elf object\n", name);
	break;
case ELF_K_AR:
	printf("%s: ar(1) archive\n", name);
case ELF_K_NONE:
	printf("%s: data\n",name);
	break;
default:
	printf("%s: unrecognized\n", name);
}
(void) elf_end(e);
(void) close(fd);

exit(EXIT_SUCCESS);


}
