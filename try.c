#include <stdio.h>
#include <stdlib.h>
#include "LIST.h"

typedef struct nodo *link;

struct nodo{
    int val;
    link next;
};

struct lista{
    link head;
    int N;
};

static link newNode(int val, link next){
    link x=malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else{
        x->val=val;
        x->next=next;
    }
    return x;
}

link listInsTail(link h,int val){
    link x;
    if (h==NULL)
        return newNode(val, NULL);
    for (x=h; x->next!=NULL; x=x->next);
    x->next=newNode(val, NULL);
    return h;
}

LIST ListaInit(){
    LIST l=malloc(sizeof LIST);
    l->head=NULL;
    l->N=0;
    return l;
}

LIST* split(LIST l, int *n){
    int i;
    LIST *vet;
    vet=malloc(l->N*sizeof(LIST)); //modifica l->N e non n
    for(i=0;i<l->N;i++){ //aggiunto
        vet[i]=ListaInit();
    }
    link x;
    x=l->head;

    if(x==NULL) //modificato x e non head
        return l;
    while(x!=NULL){
        if(x->val > x->next->val){
            i++;
        }
        vet[i]=listInsTail(vet[i],x->val);
    }
    *n=i+1;
    return vet[i];
}

void printList(LIST l) {
    link x;
    if (l==NULL)
        return;
    for (x=l->head; x!= NULL; x=x->next) {
        printf("%d\n",x->val);
    }
}
