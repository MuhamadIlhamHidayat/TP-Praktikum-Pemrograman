#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct{
	int umur;
	char nama[10];
	char jk;
}identitas;

typedef struct elmt * alamat;

typedef struct elmt{
	identitas kontainer;
	alamat next;
	alamat prev;
}elemen;

typedef struct{
	elemen* head;
	elemen* tail;
}list;

void createList(list* L){
	(*L).head = NULL;
	(*L).tail = NULL;
}

int countElemen(list L){
	int jumlah = 0;
	
	if(L.head != NULL){
		elemen* now = L.head;
	while(now != NULL){
		jumlah ++;
		now = now->next;
		}
	}
return jumlah;
}

void addFirst(list* L, char nama[],int umur, char jk){
elemen* baru = (elemen*)malloc(sizeof(elemen));
//membuat elemen baru
strcpy(baru->kontainer.nama, nama);
baru->kontainer.umur = umur;
baru->kontainer.jk = jk;

if((*L).head == NULL){
	(*L).head = baru;
	baru->prev = NULL;
	baru->next = NULL;
	(*L).tail = baru;
}
else{
	baru->next = (*L).head;
	(*L).head->prev = baru;
	(*L).head = baru;
	baru->prev = NULL;
	}
}

void addAfter(list* L, char nama[],int umur, char jk, elemen *sebelum){
if(sebelum != NULL){
	elemen* baru = (elemen*)malloc(sizeof(elemen));
	strcpy(baru->kontainer.nama, nama);
	baru->kontainer.umur = umur;
	baru->kontainer.jk = jk;
	
if(sebelum->next == NULL){
	sebelum->next = baru;
	(*L).tail = baru;
	baru->prev = sebelum;
	baru->next = NULL;
}
else{
	baru->prev = sebelum;
	baru->next = sebelum->next;
	sebelum->next->prev = baru;
	sebelum->next = baru;
		}
	}
}

void addLast(list* L, char nama[],int umur, char jk){
	if((*L).head == NULL){
		addFirst(L, nama, umur, jk);
	}
	else{
		elemen* baru = (elemen*)malloc(sizeof(elemen));
		strcpy(baru->kontainer.nama, nama);
		baru->kontainer.umur = umur;
		baru->kontainer.jk = jk;
		(*L).tail->next = baru;
		baru->next = NULL;
		baru->prev = (*L).tail;
		(*L).tail = baru;
	}
}

void delFirst(list *L){
if((*L).head != NULL){
	if(countElemen(*L) == 1){
		elemen* elhapus = (*L).head;
		(*L).head = NULL;
		(*L).tail = NULL;
		free(elhapus);
}
else{
		elemen* elhapus = (*L).head;
		(*L).head = elhapus->next;
		elhapus->next->prev = NULL;
		free(elhapus);
		}
	}
}

void delAfter(list* L, elemen *sebelum){
	if(sebelum != NULL){
		if(sebelum->next != NULL){
			elemen* elhapus = sebelum->next;
	if(elhapus->next == NULL){
	sebelum->next = NULL;
	(*L).tail = sebelum;
	elhapus->prev = NULL;
	free(elhapus);
}
		else{
			sebelum->next = elhapus->next;
			elhapus->next->prev = sebelum;
			elhapus->next = NULL;
			elhapus->prev = NULL;
			free(elhapus);
			}
		}
	}
}

void delLast(list* L){
	if((*L).head != NULL){
		if(countElemen(*L) == 1){
		delFirst(L);
		}
		else{
			elemen* elhapus = (*L).tail;
			elhapus->prev->next = NULL;
			(*L).tail = elhapus->prev;
			elhapus->prev = NULL;
			free(elhapus);
		}	
	}
}

void printElemen(list L){
	if((L).head != NULL){
	elemen* now = L.head;
	
	while(now != NULL){
		printf("prev : %d\n", now->prev);
		printf("nama : %s\n", now->kontainer.nama);
		printf("umur : %d\n", now->kontainer.umur);
		printf("jk : %c\n\n", now->kontainer.jk);
		now = now->next;
		}
	}else{
		printf("list kosong\n");
	}
	printf("\n");
}

void printElemenMundur(list L){
	if((L).head != NULL){
	elemen* now = L.tail;
	while(now != NULL){
		printf("prev : %d\n", now->prev);
		printf("nama : %s\n", now->kontainer.nama);
		printf("umur : %d\n", now->kontainer.umur);
		printf("jk : %c\n\n", now->kontainer.jk);
		now = now->prev;
	}
	}else{
		printf("list kosong\n");
	}
	printf("\n");
}

int main(){
list L;
createList(&L);

addFirst(&L, "a", 12, 'l');
//addFirst(&L, "b", 12, 'l');
addLast(&L, "b", 12, 'l');
addAfter(&L, "c", 12, 'l', L.head);

printf("==== print dari depan ====\n");
printElemen(L);

printf("==== print dari belakang ====\n");
printElemenMundur(L);
addAfter(&L, "d", 12, 'l', L.head);
delFirst(&L);

printf("==== print dari belakang ====\n");
printElemenMundur(L);
delAfter(&L, L.head);

printf("==== print dari belakang ====\n");
printElemenMundur(L);
delLast(&L);

printf("==== print dari belakang ====\n");
printElemenMundur(L);
return 0;
}
