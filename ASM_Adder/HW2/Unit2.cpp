#include <vcl.h>
#pragma hdrstop
#include "Unit2.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	Sum() ;
}
//---------------------------------------------------------------------------

void TForm2::Sum(void)
{
   BYTE ARR1[] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
   ARR2[] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}; //unsigned__bit 16

   UnicodeString comment=L"" ;
   Memo1->Lines[0].Text = L"Numbers:" ;
   comment.cat_sprintf(L"NUM1: %xH, %xH, %xH, %xH, %xH, %xH, %xH, %xH, %xH, %xH",
		ARR1[0], ARR1[1], ARR1[2], ARR1[3], ARR1[4], ARR1[5], ARR1[6], ARR1[7], ARR1[8], ARR1[9]) ;
   Memo1->Lines->Append(comment) ;
   comment = UnicodeString().sprintf(L"NUM2: %xH, %xH, %xH, %xH, %xH, %xH, %xH, %xH, %xH, %xH",
		ARR2[0], ARR2[1], ARR2[2], ARR2[3], ARR2[4], ARR2[5], ARR2[6], ARR2[7], ARR2[8], ARR2[9]) ;
   Memo1->Lines->Append(comment) ;

   asm{
		lea esi, ARR1      ; load esi as the pointer to ARR1
		add esi, 9         ; increase esi to point to MSB of ARR1
		lea edi, ARR2      ; load edi as the pointer to ARR2
		add edi, 9         ; increase edi to point to MSB of ARR2
		xor ax, ax         ; set ax as zero
		mov ecx, 00000009H ; set ecx as 9H as loop counter
		mov ah, [esi]      ; move MSB of ARR1 to ah
		add ah, [edi]      ; add MSB of ARR2 to ah
		mov [edi], ah      ; move ah to MSB of ARR2
L1:
		dec esi            ; lower esi to point to next element of ARR1
		dec edi            ; lower edi to point to next element of ARR2
		mov al, [esi]      ; move ARR1 element into ah
		adc al, [edi]      ; add ARR2 element to ah
		mov [edi], al      ; move ah to ARR2 element
		;;dec cx
		;;jnz L1
		loopnz L1
   } ;

   Memo1->Lines->Append(L"Sum:");
   comment = UnicodeString().sprintf(L"%xH, %xH, %xH, %xH, %xH, %xH, %xH, %xH, %xH, %xH",
		ARR2[0], ARR2[1], ARR2[2], ARR2[3], ARR2[4], ARR2[5], ARR2[6], ARR2[7], ARR2[8], ARR2[9]);
   Memo1->Lines->Append(comment);



}
