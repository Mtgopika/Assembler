#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
    int start,locctr,length,locdisp=8192;
    printf("\n Pass 1 of a 2 pass assembler:\n\n");
    printf("\n Loc|tLabel\tOpcode\tOperand\n");
    printf("__\t__\t__\t__\n\n");
    char opcode[20],operand[20],label[20],code[20],mneumonic[20];
    FILE*fp_in,*fp_op,*fp_sy,*fp_ou,*fp_opc,*fp_len;
    fp_in=fopen("input.txt","r");
    fp_op=fopen("optab.txt","r");
    fp_sy=fopen("symtab.txt","w");
    fp_ou=fopen("output.txt","w");
    fp_len=fopen("length.txt","w");
    fscanf(fp_in,"%s\t%s\t%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        start=atoi(operand);
        locctr=start;
        fprintf(fp_ou,"\t%s\t%s\t%s\n",label,opcode,operand);
        printf("%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        fscanf(fp_in,"%s\t%s\t%s",label,opcode,operand);
    }
    else{
        locctr=0;
        while(strcmp(opcode,"END")!=0)
        {
            fprintf(fp_ou,"%d\t",locctr);
            printf("%x\t",locdisp);
            if(strcmp(label,"**")!=0);
            fprintf(fp_sy,"%s\t%d\n",label,locctr);
            fscanf(fp_op,"%s\t%s",mneumonic,code);
            while(strcmp(mneumonic,"END")!=0)
            {
                if(strcmp(opcode,mneumonic)==0)
                {
                    locctr+=3;
                    locdisp+=3;
                    break;
                }
                fscanf(fp_op,"%s\t%s",mneumonic,code);
            }
            if(strcmp(opcode,"WORD")==0)
            {
                locctr+=3;
                locdisp+=3;
            }
            if(strcmp(opcode,"RESW")==0)
            {
                locctr+=3*(stoi(operand));
                locdisp+=3*(atoi(operand));
            }
            if(strcmp(opcode,"RESB")==0)
            {
                locctr+=atoi(operand);
                locdisp+=atoi(operand);
            }
            if(strcmp(opcode,"BYTE")==0)
            {
                locctr++;
                locdisp++;
            }
            fprintf(fp_ou,"%s\t%s\t%s\t\n",label,opcode,operand);
            printf("%s\t%s\t%s\t\n",label,opcode,operand);
            fscanf(fp_in,"%s\t%s\t%s",label,opcode,operand);
        }
        fprintf(fp_ou,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        printf("\t%s\t%s\t%s\n",label,opcode,operand);
        length=locctr-start;
        printf("\nStarting adress:%d\n",start);
        fprintf(fp_len,"%d",length);
        fclose(fp_len);
        fclose(fp_in);
        fclose(fp_op);
        fclose(fp_sy);
        fclose(fp_ou);
    }
}




            
            
        
                