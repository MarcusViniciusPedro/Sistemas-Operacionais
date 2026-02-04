#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex; // Semáforo para controle de acesso à seção crítica
int contador = 0; // Variável compartilhada entre as threads

void* thread(void* arg) {
    int id = *((int*)arg); // Identificador da thread

	//Operação de espera ou bloqueio 
    //Caso o valor do semáforo for maior que zero, será decrementado, e a thread continua sua execução (livre).
    //Se o valor for zero, a thread será bloqueada até que o semáforo seja liberado.
    sem_wait(&mutex); 
    printf("\nThread %d entrou na seção crítica.\n", id);

    // Seção crítica
    contador++; //incrementação de valores
    printf("Thread %d atualizou contador para: %d\n", id, contador);
    sleep(4); //Simula uma tarefa que leva certo tempo, nesse caso 4 segundos.

    printf("Thread %d saiu da seção crítica.\n", id);
    sem_post(&mutex); 
	//Operação de liberação ou sinalização.
    //A thread incrementa o semáforo, permitindo outra thread que estava bloqueada.
}

int main() {
    sem_init(&mutex, 0, 1); //inicialização do semáforo 
	// O 0 indica se o semáforo está sendo compartilhado por threads do mesmo processo
	// O 1 é o valor inicial do semáforo

    pthread_t t1, t2; //declaração das threads
    int id1 = 1, id2 = 2; //definindo valor das threads

    pthread_create(&t1, NULL, thread, &id1); // Cria a thread t1 com id 1
    sleep(2); //A thread principal dorme por 2 segundos, enquanto a primeira adquire o semáforo, entrando na seção crítica antes que a segunda seja criada.
    pthread_create(&t2, NULL, thread, &id2); // Cria a thread t2 com id 2, a qual tentará adquirir o semáforo, contudo será bloqueada, pois t1 já adquiriu.

    pthread_join(t1, NULL); //O thread principal espera que t1 termine sua execução.
    pthread_join(t2, NULL); //O thread principal espera que t2 termine sua execução.

    sem_destroy(&mutex); //Libera os recursos do semáforo.

    printf("\nValor final do contador: %d\n", contador);
    printf("Finalização do programa\n");

    return 0;
}

