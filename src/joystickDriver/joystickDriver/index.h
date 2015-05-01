#ifndef index_h
#define index_h

typedef struct{

		uint8_t max;
		uint8_t current;

}Tindex;


Tindex* index(void){
	
	Tindex *idx = malloc(sizeof(Tindex));
	idx->max=8;
	idx->current=0;
	return idx;
}

inline void next(Tindex *index){
	
	index->current++;
	index->current%=index->max;
	
	
}
#endif