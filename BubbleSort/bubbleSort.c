#include <stdio.h>
#include <time.h>

int a[5] = {11, 3, 44, 22, 9};
int n = 5;

void sort() {
	clock_t start = clock();
	asm("xorl	%ecx, %ecx \n"
		"\txorl	%edx, %edx \n"
		"\tmovl n(%rip), %r10d\n"
		"\tsubl	$1, n(%rip)\n"
		"\tmovl	n(%rip), %r11d\n"
		"\tleaq	a(%rip), %rbx \n"	
		"Cycle: \n"
		"\tcmpl	%r10d, %ecx \n"// первый счётчик(i)
		"\tje	EndOfCycle \n"
		"\tcmpl	%r11d, %edx \n"// второй счётчик(j)
		"\tje 	NextElem \n"
		"\tmovq %rbx, %rax \n"
		"\taddq	$4, %rax \n"
		"\tmovl	(%rbx), %r8d \n"
		"\tcmpl	(%rax), %r8d \n"
		"\tjle	NextIsBigger \n"// если некст больше, то не свапаем(сортировка по возрастанию)
		"\tmovl	(%rax), %r9d \n"// swap элементов
		"\tmovl	%r9d, (%rbx) \n"
		"\tmovl	%r8d, (%rax) \n"
		"NextIsBigger:\n"
		"\taddq	$4, %rbx \n"// переход при том же i на новый j
		"\tincl	%edx \n"
		"\tjmp	Cycle \n"
		"NextElem: \n"
		"\tleaq	a(%rip), %rbx \n"// переход на новый i, j=0
		"\tincl	%ecx \n"
		"\txorl	%edx, %edx \n"
		"\tjmp Cycle \n"
		"EndOfCycle: \n");
	clock_t end = clock();
	double sec = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%f\n", sec);
}

int main() {
	sort();
	for (int i = 0; i < 5; ++i)
		printf("%d\n", a[i]);
	 return 0;
}
