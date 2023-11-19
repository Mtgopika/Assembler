#include <stdio.h>
#include <string.h>
int main() {
  FILE *fp_ou, *fp_op, *fp_len, *fp_sy, *fp_opc, *fp_samp, *fp_read;
  int i, j, len, reclen = 0, loc;
  char symnam[5], code[5], start[10], label[20], opcode[10], operand[10],
      symloc[10], mnemonic[10], a[20], b[20], count[20], s;
  fp_ou = fopen("output.txt", "r");
  fp_len = fopen("length.txt", "r");
  fp_op = fopen("optab.txt", "r");
  fp_sy = fopen("symtab.txt", "r");
  fp_opc = fopen("optab.txt", "r");
  fp_samp = fopen("sample.txt", "w");
  printf("\n pass 2 of a two pass assembler :\n");
  printf(" ______________\n\n");
  printf("Header Record :\n");
  fscanf(fp_ou, "\t%s\t%s\t%s\n", label, opcode, operand);
  if (strcmp(opcode, "START") == 0) 
  {
    strcpy(start, operand);
    fscanf(fp_len, "%d", &len);
  }
  printf("H^%s^00%s^0000%X\t", label, start, len);
  printf("\n Text Record:\n");
  printf("T^00%s^", start);
  reclen = reclen + 6;
  fscanf(fp_ou, "%d\t%s\t%s\t%s", &loc, label, opcode, operand);
  while (strcmp(opcode, "END") != 0)
    {
    fscanf(fp_op, "%s%s", mnemonic, code);
    while (!feof(fp_op))
      {
      if (strcmp(opcode, mnemonic) == 0)
      {
        fscanf(fp_sy, "%s\t%s", symnam, symloc);
        while (!feof(fp_sy))
          {
          if (strcmp(operand, symnam) == 0)
          {
            reclen += 6;
            fprintf(fp_samp, "%s%s^", code, symloc);
            break;
          } else
            fscanf(fp_sy, "%s%s", symnam, symloc);
        }
        break;
      } else
        fscanf(fp_op, "%s%s", mnemonic, code);
    }
    if ((strcmp(opcode, "BYTE") == 0) || (strcmp(opcode, "WORD") == 0)) {
      if (strcmp(opcode, "WORD") == 0) {
        fprintf(fp_samp, "00000%s^", operand);
        reclen += 6;
      } else {
        for (i = 0, j = 2; j < (strlen(operand) - 1); i++, j++)
          count[i] = operand[2];
        count[i] = '\0';
        while (!feof(fp_opc)) {
          fscanf(fp_opc, "%s\t%s", a, b);
          if (strcmp(count, a) == 0) {
            fprintf(fp_samp, "0000%s", b);
            reclen += 6;
          }
        }
      }
    }
    fscanf(fp_ou, "%d %s%s%s", &loc, label, opcode, operand);
    fseek(fp_op, SEEK_SET, 0);
    fseek(fp_sy, SEEK_SET, 0);
  }
  fclose(fp_samp);
  fp_read = fopen("sample.txt", "r");
  printf("%X^", reclen / 2);
  while ((s = fgetc(fp_read)) != EOF)
    printf("%c", s);
  printf("\n End Record :");
  printf("\nE^00%s\n\n", start);
  fclose(fp_ou);
  fclose(fp_op);
  fclose(fp_sy);
  fclose(fp_len);
  fclose(fp_read);
}
