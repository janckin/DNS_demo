#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXHASH 220

struct hashData{
	char* domain;
	char* ip;
	int del;
};

int convertHash(char* domain){
	int hash = 0, i;
	int len = strlen(domain);
	for(i = 0; i < len; i++){
		hash += 131 * domain[i];
	}
	hash = hash % MAXHASH;
	
	return hash;
}

int addHash(struct hashData* hashTable, char* domain, char* ip){
	int i;
	int hash = convertHash(domain);
	//printf("the hash value is: %s\n", hashTable[hash].domain);
	if(hashTable[hash].domain == NULL || hashTable[hash].del == 1){
		hashTable[hash].domain = domain;
		hashTable[hash].ip = ip;
		//printf("we get 1\n");
	}else if(!strcmp(hashTable[hash].domain, domain)){
		//printf("we get 3\n");
		hashTable[hash].ip = ip;
	}else{
		for(i = 0; i < MAXHASH; i++){
			hash = (hash + 1) % MAXHASH;
			if(hashTable[hash].domain == NULL || hashTable[hash].del == 1){
				hashTable[hash].domain = domain;
				hashTable[hash].ip = ip;
				//printf("we get 2\n");
				return 1;
			}else if(!strcmp(hashTable[hash].domain, domain)){
				hashTable[hash].ip = ip;
				return 1;
			}
		}
	}
	return 1;
}

int findHash(struct hashData* hashTable, char* domain){
	int i, result;
	int hash = convertHash(domain);
	result = -1;
	if(hashTable[hash].domain == NULL || hashTable[hash].del == 1){
		printf("no such data!\n");
		return result;
	}
	//printf("first: %s\n", hashTable[hash].domain);
	if(!strcmp(hashTable[hash].domain, domain)){
		result = hash;
	}else{
		for(i = 0; i < MAXHASH; i++){
			hash = (hash + 1) % MAXHASH;
			//printf("%d time: %s\n", i, hashTable[hash].domain);
			if(hashTable[hash].domain == NULL || hashTable[hash].del == 1){
				printf("no such data!\n");
				return result;
			}
			if(!strcmp(hashTable[hash].domain, domain)){
				result = hash;
				return result;
			}
		}
	}

	return result;
}

int deleteHash(struct hashData* hashTable, char* domain){
	int delHash;
	delHash = findHash(hashTable, domain);
	if(delHash == -1){
		printf("There is no such data!\n");
		return 0;
	}else{
		hashTable[delHash].del = 1;
	}
	printf("delete success!\n");
	return 1;
}


int initHash(struct hashData* hashTable, int len){
	int i;
	char* domain, * ip;
	char* prefix = "www.tplink";
	char* post = ".com.cn";
	char* initIp = "192.168.50.";
	if(len > MAXHASH){
		printf("length must be less than %d\n", MAXHASH);
		return 0;
	}
	for(i = 0; i < MAXHASH; i++){
		hashTable[i].domain = NULL;
		hashTable[i].ip = NULL;
		hashTable[i].del = 0;
	}
	for(i = 0; i < len; i++){
		domain = (char*)malloc(20);
		ip = (char*)malloc(15);
		//printf("%d\n", i);
		sprintf(domain, "%s%d%s", prefix, i, post);
		sprintf(ip, "%s%d", initIp, i);
		addHash(hashTable, domain, ip);
		
	}
	
	return 1;
}

