/*
  Copyright (c) 2014, Alexey Frunze
  2-clause BSD license.
*/
#ifdef _DOS

#ifdef __HUGE__
static
int DosClose(int handle, unsigned* error)
{
  asm("mov ah, 0x3e\n"
      "mov bx, [bp + 8]\n"
      "int 0x21");
  asm("movzx ebx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and eax, 1\n"
      "mov esi, [bp + 12]\n"
      "ror esi, 4\n"
      "mov ds, si\n"
      "shr esi, 28\n"
      "mov [si], ebx");
}
#endif // __HUGE__

#ifdef __SMALLER_C_16__
static
int DosClose(int handle, unsigned* error)
{
  asm("mov ah, 0x3e\n"
      "mov bx, [bp + 4]\n"
      "int 0x21");
  asm("mov bx, ax\n"
      "cmc\n"
      "sbb ax, ax\n"
      "and ax, 1\n"
      "mov si, [bp + 6]\n"
      "mov [si], bx");
}
#endif // __SMALLER_C_16__

int close(int fd)
{
  unsigned error;
  if (DosClose(fd, &error))
    return 0;
  return -1;
}
#endif // _DOS
