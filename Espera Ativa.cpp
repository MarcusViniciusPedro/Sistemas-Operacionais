#include <stdio.h>
#include <stdatomic.h> // Em ambientes modernos, usar atômicos é mais seguro
// Em um contexto educacional para demonstrar o CONCEITO:
// volatile int lock = 0; // Variável de bloqueio, 0=livre, 1=ocupado

// Usando atomic_flag para simular o TSL/Test-and-Set para correção (melhor prática moderna)
atomic_flag lock = ATOMIC_FLAG_INIT;

void entrar_secao_critica() {
    // Loop de Espera Ativa (Spinlock):
    // Tenta adquirir o bloqueio. Se 'test_and_set' retorna 'true', 
    // significa que o flag já estava "setado" (ocupado), então ele espera.
    // Se retorna 'false', significa que o flag estava "clear" (livre) 
    // e o TSL o "setou" (ocupou) atomicamente.
    while (atomic_flag_test_and_set(&lock)) { 
        // Espera Ativa: O processo fica em loop, consumindo CPU, 
        // até que o lock seja liberado por outro processo.
    }
    
    // *** SEÇÃO CRÍTICA ***
    printf("Processo entrou na Seção Crítica.\n");
    // ... Código para acessar recurso compartilhado ...
    printf("Processo saindo da Seção Crítica.\n");
    // *** FIM DA SEÇÃO CRÍTICA ***
    
    // Libera o bloqueio
    atomic_flag_clear(&lock);
}

// Demonstração (pode-se adicionar threads para testar a concorrência)
int main() {
    entrar_secao_critica();
    // Um segundo processo tentaria entrar, mas ficaria em Espera Ativa no 'while'
    // até que o primeiro processo chame atomic_flag_clear().
    return 0;
}
