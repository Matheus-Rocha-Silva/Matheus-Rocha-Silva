//
// Created by theus on 05/06/25.
//

#ifndef PROJETOSC_HASH_TABLE_H
#define PROJETOSC_HASH_TABLE_H

#endif //PROJETOSC_HASH_TABLE_H
typedef struct{
    char *chave;
    char *valor;
}ht_item;

typedef struct{
    int tamanho;
    int contagem;
    ht_item **itens;
}ht_hash_table;

void ht_inserir(ht_hash_table *ht, const char *chave, const char *valor);
char *ht_pesquisar(ht_hash_table *ht, const char *chave);
void ht_deletar(ht_hash_table *h, const char *chave);