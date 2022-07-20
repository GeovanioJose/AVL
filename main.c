#include"avl.h"
#include <unistd.h>
#include <ctype.h>
#include<string.h>

int main(int argc, char **argv){
	AVL* avl = (AVL*)malloc(sizeof(AVL));
	no_avl* temp = NULL;
	int aflag = 0;
	int bflag = 0;
	int num = 0;
	int index;
	int c;
	int cont = 0; 
	char *cvalue = NULL;
	int i;
	for(i = 0; i < argc; i++){
		cvalue = argv[i];
		if((strcmp(cvalue, "-m") == 0) | (strcmp(cvalue, "-M") == 0) | (strcmp(cvalue, "-a") == 0) | (strcmp(cvalue, "-s") == 0)){
			cont++;
		}
	}		
	
	opterr = 0;
	if(cont < 2){  
		while ((c = getopt (argc, argv, "hf:o:mMa:s:")) != -1){
	  
		 	 switch (c){   
	        
				case 'h':
					aflag = 0;			
			     	help();
			    		break;
		          case 'f':
		          	aflag = 2;		          	
		          	lerArquivo(avl, optarg);
			     	break;
			     case 'o':		          	
			          aflag = 0;		     	     	
		     	     treeSalvar(avl, optarg);
					break; 
		          case 'm':		          	
			          aflag = 0;		     	     	
		     	     temp = treeMin(avl->raiz);
					if(temp != NULL){
						printf("%d\n", temp->chave);		
				 	}
					break;         	
		          	
				case 'M':					
			          aflag = 0;		     	     
		     	     temp = treeMax(avl->raiz);
					if(temp != NULL){
						printf("%d\n", temp->chave);		
				 	}
					break;				
				case 'a':					
					aflag = 0;							 
					num = atoi(optarg);
					temp = treeAnt(avl->raiz, lerNo(num));
					if(temp != NULL){
						printf("%d\n", temp->chave);		
				 	}else{
				 		fprintf (stderr, "-1\n");
				 	}
					break;
					
				case 's':
					aflag = 0;					
					num = atoi(optarg);
					temp = treeSuc(avl->raiz, lerNo(num));
					if(temp != NULL){
						printf("%d\n", temp->chave);		
				 	}else{
				 		fprintf (stderr, "-1\n");
				 	}
					break;
									 
			    case '?':
				if (optopt == 'c')
					fprintf (stderr, "Opção -%c requer um argumento.\n", optopt);
			     else if (isprint (optopt))
					fprintf (stderr, "Opção desconhecida `-%c'.\n", optopt);
			     else
					fprintf (stderr,"Caractere de opção desconhecida `\\x%x'.\n", optopt);
				
					return 1;
			    default:
			     abort ();
				
				}
	}		
	}else{
		fprintf (stderr, "ERRO: parâmetros conflitantes\n");
	     
	}
	if(aflag == 2){
		exibirPreOrdem(avl->raiz);
		printf("\n");
	}
	
	return 0;
}



			

