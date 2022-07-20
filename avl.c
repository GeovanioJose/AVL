#include"avl.h"
#include<math.h>
#include<string.h>

void help(){

	printf("-h			: mostra o help\n");
	printf("-o <arquivo>		: redireciona a saida para o ‘‘arquivo’’\n");
	printf("-f <arquivo>		: indica o ‘‘arquivo’’ que contém os dados a serem adicionados na AVL\n");
	printf("-m			: imprime o menor elemento da AVL\n");
	printf("-M			: imprime o maior elemento da AVL\n");
	printf("-a <elemento>		: imprime o antecessor na AVL do ‘‘elemento’’ ou caso contrário imprime -1\n");
	printf("-s <elemento>		: imprime o sucessor na AVL do ‘‘elemento’’ ou caso contrário imprime -1\n");
};

no_avl* treeMax(no_avl* raiz){
	if(raiz->dir != NULL && raiz != NULL){
		treeMax(raiz->dir);
	}else{
		return raiz;
	}
};

no_avl* treeMin(no_avl* raiz){
	if(raiz->esq != NULL && raiz != NULL){
		treeMin(raiz->esq);
		
	}else{
		return raiz;
	}
};

no_avl* treeSuc(no_avl* raiz, no_avl* dado){
	no_avl* aux;
	aux = treeBusca(raiz, dado);
	if(aux != NULL){
		if(aux->dir != NULL && raiz != NULL)
			return treeMin(aux->dir);
	
		no_avl* y = aux->pai;
		while(y != NULL && aux == y->dir){
			aux = y;
			y = y->pai;	
		}
		return y;
	}else{
		return NULL;
	}
};

no_avl* treeAnt(no_avl* raiz, no_avl* dado){
	no_avl* aux;
	aux = treeBusca(raiz, dado);
	if(aux != NULL){
		if(aux->esq != NULL && raiz != NULL)
			return treeMax(aux->esq);
		
		no_avl* y = aux->pai;
		while(y != NULL && aux == y->esq){
			aux = y;
			y = y->pai;	
		}
		return y;
	}else{
		return NULL;
	}		
};

no_avl* treeBusca(no_avl* raiz, no_avl* dado){
	if(raiz != NULL){
		if(raiz->chave == dado->chave){
			return raiz;		
		}else{	
			if(dado->chave > raiz->chave){
				return treeBusca(raiz->dir, dado);
			}else{
				return treeBusca(raiz->esq, dado);
			}
		}
	}
};

no_avl* rotacaoDir(no_avl* raiz){
	no_avl* temp1 = raiz;
	no_avl* temp2 = temp1->esq;	
	
	raiz->esq = temp2->dir;		
	
	if(temp2->dir != NULL){	
		temp2->dir->pai = raiz;	
	}
	temp2->dir = raiz;
	
	if(raiz->pai != NULL){
		
		if(raiz->pai->dir == temp2->pai){			
			raiz->pai->dir = temp2;
		}
		if(raiz->pai->esq == temp2->pai){			
			raiz->pai->esq = temp2;
		}		
	}
	temp2->pai = temp1->pai;
	temp1->pai = temp2;		
	temp1 = temp2;
	return temp1;
	
};
no_avl* rotacaoEsq(no_avl* raiz){
	no_avl* temp1 = raiz;
	no_avl* temp2 = temp1->dir;
	
	raiz->dir = temp2->esq;
	
	if(temp2->esq != NULL){	
		temp2->esq->pai = raiz;	
	}
	
	temp2->esq = raiz;	
	
	if(raiz->pai != NULL){
		
		if(raiz->pai->dir == temp2->pai){			
			raiz->pai->dir = temp2;
		}
		if(raiz->pai->esq == temp2->pai){			
			raiz->pai->esq = temp2;
		}		
					
	}
	temp2->pai = temp1->pai;
	temp1->pai = temp2;	
	temp1 = temp2;		
	return temp1;		
		
};
no_avl* rotacaoDuplaDir(no_avl* raiz){
	raiz = rotacaoEsq(raiz->esq);
	raiz = rotacaoDir(raiz->pai);	
	return raiz;
};
no_avl* rotacaoDuplaEsq(no_avl* raiz){	
	raiz = rotacaoDir(raiz->dir);	
	raiz = rotacaoEsq(raiz->pai);
	return raiz;
};

int maior(int x, int y){
	if(x > y)
		return x;
	else
		return y;
};


int altura(no_avl* raiz){	
	int u, v;
	if (raiz == NULL) return -1;
	u = altura(raiz->esq);
	v = altura(raiz->dir);
	if (u > v) return u+1;
	else return v+1;
};

no_avl* lerNo(int valor){
	no_avl* novo = (no_avl*)malloc(sizeof(no_avl));
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = NULL;
	novo->chave = valor;
	
	return novo;
	
};

int fator(no_avl* raiz){
	return altura(&(*(raiz)->esq)) - altura(&(*(raiz)->dir));
};

int treeInserir(AVL* avl, no_avl* dado){
	no_avl* ant = NULL;
	no_avl* atual = avl->raiz;	
	while(atual != NULL){
		ant = atual;
		if(dado->chave == atual->chave){
			free(dado);
			return 0;
		}	
		
		if(dado->chave > atual->chave){
			atual = atual->dir;		
		}else{
			atual = atual->esq;
		}
	}
	dado->pai = ant;
	if(ant == NULL){
		avl->raiz = dado;
	}else{ 
		if( dado->chave > ant->chave)
			ant->dir = dado;	
		else
			ant->esq = dado;
	}		
	no_avl* temp = dado;
	no_avl* ant2 = NULL;
	
	while(temp != NULL){		
		no_avl* aux = temp;		
		if((altura((aux)->esq) - (altura((aux)->dir)) == 2)){
			if(altura((aux)->esq->esq) >  (altura((aux)->esq->dir))){
				temp = rotacaoDir(temp);																			
			}else{
				temp = rotacaoDuplaDir(temp);
			}	
		}else{
			aux = temp;	
			if((altura((aux)->esq) - (altura((aux)->dir))) == -2){
				if(altura((aux)->dir->dir) > (altura((aux)->dir->esq))){
					temp = rotacaoEsq(temp);									
				}else{	
					temp = rotacaoDuplaEsq(temp);				
				}
			}
		}
		ant2 = temp;
		temp = temp->pai;
	}	
	
	avl->raiz = ant2;
	
	return 1;
		
};

void lerArquivo(AVL* avl, char *argv){	
	FILE *fp;	
	int dado = 0;
	no_avl* dado1 = (no_avl*) malloc(sizeof(no_avl));	
	int cont = 0;
	int i;
	for(i = strlen(argv) - 3; i < strlen(argv);i++){
		if(argv[i] == 'b' ^ argv[i] == 'i' ^ argv[i] == 'n'){
			cont++;
		}	
	}
	if(cont == 3){
		fp = (FILE *) fopen(argv, "rb");	
		if(fp != NULL){			
			while((fread(dado1, sizeof(no_avl), 1, fp))){
				treeInserir(avl, lerNo(dado1->chave));
			}		
			fclose(fp);		
		}else{
			printf("Erro na abertura do arquivo!bin\n");
		}
	
	}else{
		fp = (FILE *) fopen(argv, "r");	
		if(fp != NULL) {
			while(fscanf(fp, "%i\n", &dado) != EOF){
					treeInserir(avl, lerNo(dado));
			}		
			fclose(fp);		
		}else{
			printf("Erro na abertura do arquivo!\n");
		}	
	}


};


void treeSalvar(AVL* avl, char *argv){
	FILE *fp;	
	no_avl *dado = (no_avl *) malloc(sizeof(no_avl));	
	fp = (FILE *) fopen(argv, "wb");	
	if(fp != NULL) {
		lerTree(avl->raiz, fp);
		fclose(fp);		
	}else{
		printf("Erro na abertura do arquivo!\n");
	}
};

void lerTree(no_avl* raiz, FILE *fp){
	if(raiz != NULL){
		fprintf(fp, " (");
		fprintf(fp, "%i", (raiz)->chave);
		if(raiz->esq == NULL ^ raiz->dir == NULL){
			fprintf(fp, " (x)");
		}		
		lerTree(raiz->esq, fp);
		lerTree(raiz->dir, fp);
		fprintf(fp, ")");
	}
};

void exibirEmOrdem(no_avl* raiz){
	if(raiz != NULL){
		exibirEmOrdem(&(*(raiz->esq)));
		printf("%d\t", (raiz)->chave);
		exibirEmOrdem(&(*(raiz->dir)));
	}
}
void exibirPreOrdem(no_avl* raiz){
	if(raiz != NULL){
		printf(" (");
		printf("%d", (raiz)->chave);
		if(raiz->esq == NULL ^ raiz->dir == NULL){
			printf(" (x)");
		}		
		exibirPreOrdem(&(*(raiz->esq)));
		exibirPreOrdem(&(*(raiz->dir)));
		printf(")");
	}
		
}

void exibirPosOrdem(no_avl* raiz){
	if(raiz != NULL){
		exibirPosOrdem(&(*(raiz->esq)));
		exibirPosOrdem(&(*(raiz->dir)));
		printf("%d\n", (raiz)->chave);
	}
}

