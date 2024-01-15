# Philosophers

~ Started on: 27/12/2023 ~ *** ~ WORK IN PROGRESS ~~~ 

[![Stars](https://img.shields.io/github/stars/Sulig/Philosophers?color=ffff00&label=Stars&logo=Stars&style=?style=flat)](https://github.com/Sulig/Philosophers)
[![Size](https://img.shields.io/github/repo-size/Sulig/Philosophers?color=blue&label=Size&logo=Size&style=?style=flat)](https://github.com/Sulig/Philosophers)
[![Activity](https://img.shields.io/github/last-commit/Sulig/Philosophers?color=orange&label=Last%20Commit&style=flat)](https://github.com/Sulig/Philosophers)
 
***
Resumen:
En este proyecto, aprenderás los principios básico de hilar un proceso.
Vas a aprender a como crear hilos y descubrirás los mutex.

***
## Contenido del repositorio:
- Philosophers *in progress*
- [Subject](https://github.com/Sulig/Philosophers/blob/master/Philosophers.pdf)

***
## Comandos Esenciales:


***
~ Made by sadoming ~
***


// Saved 4 later -> 
1 Segundo -> 1000 milisegundos
1 milisegundo -> 1000 microsegundos

``` c
size_t    get_current_time(void)
{
    struct timeval    time;

    if (gettimeofday(&time, NULL) == -1)
        write(2, "gettimeofday() error\n", 22);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
```
