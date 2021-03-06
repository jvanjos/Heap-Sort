// Heap.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::ifstream arquivo;
std::vector<int> vetor;
#include <stdio.h>
#define true 1
#define false 0

typedef struct {
	std::vector<int> A;
	int tamanhoAtual;
} HEAP;

int pai(int i) {
	return i / 2;
}

int filhoEsquerda(int i) {
	return 2 * i;
}

int filhoDireita(int i) {
	return 2 * i + 1;
}

void inicializarHeap(HEAP * h) {
	h->A.push_back(0);
	h->tamanhoAtual = 0;
}

/* metodo auxiliar que pressupoe que o heap para qualquer j>i estah ordenado
porem o elemento i nao eh necessariamente maior que seus filhos           */
void maxHeapify(HEAP * h, int i) {
	int esq = filhoEsquerda(i);
	int dir = filhoDireita(i);
	int temp;
	int maior = i;
	if ((esq <= h->tamanhoAtual) && (h->A[esq] > h->A[i])) maior = esq;
	if ((dir <= h->tamanhoAtual) && (h->A[dir] > h->A[maior])) maior = dir;
	if (maior != i) {
		temp = h->A[i];
		h->A[i] = h->A[maior];
		h->A[maior] = temp;
		maxHeapify(h, maior);
	}
}

// Constroi heap a partir do arranjo usando o metodo maxHeapify
void construirHeapMaximo(HEAP * h) {
	int i;
	int metadeTamanho = h->tamanhoAtual / 2;
	for (i = metadeTamanho; i > 0; i--) maxHeapify(h, i);
}

// Insere no final do arranjo do heap
bool inserirForaDeOrdem(HEAP * h, int valor) {
	(h->tamanhoAtual)++;
	h->A.push_back(valor);
	return true;
}


// Imprime o arranjo (na ordem que estiver)
void imprimirArranjo(HEAP h) {
	int tamanho = h.tamanhoAtual;
	int i;
	for (i = 1; i <= tamanho; i++) printf("%d ", h.A[i]);
	printf("\n");
}


// Imprime elementos em ordem decrescente e esvazia o heap
void heapSort(HEAP * h) {
	int tamanho = h->tamanhoAtual;
	int i, temp;
	construirHeapMaximo(h);
	for (i = tamanho; i > 1; i--) {
		temp = h->A[1];
		h->A[1] = h->A[i];
		h->A[i] = temp;
		(h->tamanhoAtual)--;
		maxHeapify(h, 1);
	}
	//printf("\n");
	h->tamanhoAtual = tamanho;;
}

bool inserirHeap(HEAP * h, int chave) {
	int i, temp;
	(h->tamanhoAtual)++;
	i = h->tamanhoAtual;
	h->A.push_back(chave);
	while ((i > 1) && (h->A[pai(i)] < h->A[i])) {
		temp = h->A[i];
		h->A[i] = h->A[pai(i)];
		h->A[pai(i)] = temp;
		i = pai(i);
	}
	return true;
}

int alturaHeap(HEAP* h) {
	int altura = -1;
	int i = 1;
	while (i <= h->tamanhoAtual) {
		i = filhoEsquerda(i);
		altura++;
	}
	return altura;
}


int main() {
	HEAP meuHeap;
	inicializarHeap(&meuHeap);
	std::string arquivoname;
	std::cout << "Heap Sort:" << std::endl << "Digite o nome do arquivo(ex. exemplo.txt): ";
	std::cin >> arquivoname;

	arquivo.open(arquivoname.data());
	if (!arquivo.is_open()) {
		system("pause");
		return -1;
	}
	int i, j, aux;
	std::string stringer;
	while (!arquivo.eof()) {
		std::getline(arquivo, stringer);
		int num = std::stoi(stringer);
		inserirForaDeOrdem(&meuHeap,num);
	}
	printf("Desodernado:\n");
	imprimirArranjo(meuHeap);
	heapSort(&meuHeap);
	printf("Odernado:\n");
	imprimirArranjo(meuHeap);
	system("pause");
	return 0;

}
