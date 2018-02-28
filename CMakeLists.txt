cmake_minimum_required(VERSION 3.9)
project(pizza)

set(CMAKE_C99_STANDARD 11)

add_executable(pizza
        pizza.h
        error_handle.c
        ingr_count.c
        pizza.c
        read.c
        set_scopes.c
        sort.c
        ft_strsplit.c
        cut_pizza.c)