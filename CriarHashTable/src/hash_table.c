//
// Created by theus on 05/06/25.
//

#include <stdio.h>
#include <string.h>

#include "hash_table.h"

static ht_item HT_ITEM_DELETADO = {NULL, NULL};


static ht_item *ht_new_item(const char *k, const char *v){
    ht_item *i = malloc(sizeof(ht_item));
    i -> chave = strdup(k);
    i -> valor = strdup(v);
    return i;
}

ht_hash_table *ht_new(){
    ht_hash_table *ht = malloc(sizeof(ht_hash_table));

    ht -> tamanho = 53;
    ht -> contagem = 0;
    ht -> itens = calloc((tamanho_t)ht -> tamanho, sizeof(ht_item*));
    return ht;
}

// Funcão para deletar itens de hash table e liberar memória alocada
static void ht_deletar_item(ht_item *i){
    free(i->chave);
    free(i->valor);
    free(i);
}

void ht_deletar_hash_table(ht_hash_table *ht){
    for(int i = 0; i < ht->tamanho; i++){
        ht_item *item = ht->itens[i];
        if(item != NULL){
            ht_deletar_item(item);
        }
    }
    free(ht -> itens);
    free(ht);
}

static int ht_hash(const char *s, const int a, const int m){
    long hash = 0;
    const int len_s = strlen(s);
    for(int i = 0; i < len_s; i++){
        hash =+ (long)pow(a, len_s - (i + 1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}

static int ht_get_hash(const char *s, const int num_buckets, const int tentativa){
    const int hash_a = ht_hash(s, HT_PRIMO_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIMO_2, num_buckets);
    return (hash_a + (tentativa * (hash_b + 1))) % num_buckets;
}

void ht_inserir(ht_hash_table *ht, const char *chave, const char *valor){
    ht_item *item = ht_new_item(chave, valor);
    int indice = ht_get_hash(item -> chave, ht -> tamanho, 0);
    ht_item *item_atual = ht -> itens[indice];
    int i = 1;
    //Ao inserir em um nodo vazio será possível inserir um novo nodo no slot deletado
    while(item_atual != NULL){
        if(item_atual != &HT_ITEM_DELETADO){
            if(strcmp(item_atual -> chave, chave) == 0){
                ht_deletar_item(item_atual);
                ht ->itens[indice] = item;
                return;
            }
        }
    }
    /*while(item_atual != NULL && item_atual != &HT_ITEM_DELETADO){
        indice = ht_get_hash(item -> chave, ht -> tamanho, i);
        item_atual = ht -> itens[indice];
        i++;
    }*/
    ht -> itens[indice] = item;
    ht -> contagem++;
}

char *ht_pesquisar(ht_hash_table *ht, const char *chave){
    int indice = ht_get_hash(chave, ht -> tamanho, 0);
    ht_item *item = ht -> itens[indice];
    int i = 1;
    while(item != NULL){
        if(item != &HT_ITEM_DELETADO){
            if(strcmp(item -> chave, chave) == 0){
                return item -> valor;
            }
        }
        indice = ht_get_hash(chave, ht -> tamanho, i);
        item = ht -> itens[indice];
        i++;
    }
    return NULL;
}



void ht_deletar(ht_hash_table *ht, const char *chave){
    int indice = ht_get_hash(chave, ht -> tamanho, 0);
    ht_item *item = ht -> itens[indice];
    int i = 1;
    while(item != NULL){
        if(item != &HT_ITEM_DELETADO){
            if(strcmp(item -> chave, chave) == 0){
                ht_deletar_item(item);
                ht -> itens[indice] = &HT_ITEM_DELETADO;
            }
        }
        indice = ht_get_hash(chave, ht->tamanho, i);
        item = ht -> itens[indice];
        i++;
    }
    ht->contagem++;
}

static ht_hash_table  *ht_novo_tamanho(const int tamanho_base){
    ht_hash_table *ht = malloc(sizeof(ht_hash_table)); // trocar de xmalloc() para malloc()
    ht -> tamanho_base = tamanho_base;
    ht -> tamanho= proximo_primo(ht -> tamanho_base);

    ht -> contagem = 0;
    ht -> itens = xcalloc((tamanho_t)ht->tamanho, sizeof(ht_item*));
    return ht;
}

ht_hash_table *ht_new(){
    return tamanho_novo_ht(HT_TAMANHO_BASE_INCIAL);
}

static void ht_redim(ht_hash_table *ht, const int tamanho_base){
    if(tamanho_base < HT_TAMANHO_BASE_INICIAL){
        return;
    }
    ht_hash_table *novo_ht = ht_novo_tamanho(tamanho_base);
    for(int i = 0; i < ht -> tamanho; i++){
        ht_item *item = ht -> itens[i];
        if(item != NULL && item != &HT_ITEM_DELETADO){
            ht_inserir(novo_ht, item -> chave, item -> valor);
        }
    }
    ht -> tamanho_base = novo_ht -> tamanho_base;
    ht -> contagem = novo_ht -> contagem;

    // Deletar novo_ht
    const int tamanho_temp = ht -> tamanho;
    ht -> tamanho = novo_ht -> tamanho;
    novo_ht -> tamanho = tamanho_temp;

    ht_item **itens_temp = ht -> itens;
    ht -> itens = novo_ht -> itens;
    novo_ht -> itens = itens_temp;

    ht_deletar_hash_table(novo_ht);
}

static void ht_redim_up(ht_hash_table *ht){
    const int novo_tamanho = ht -> tamanho_base * 2;
    ht_redim(ht, novo_tamanho);
}

static void ht_redim_down(ht_hash_table *ht){
    const int novo_tamanho = ht -> tamanho_base / 2;
    ht_redim(ht, novo_tamanho);
}