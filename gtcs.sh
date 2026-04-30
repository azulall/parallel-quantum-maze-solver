#!/bin/bash

# Hata kontrolü: Eğer bir komut hata verirse scripti durdurma, devam et.
set +e 

mkdir -p test_cases
gcc -O3 maze_generator.c -o maze_gen

sizes=(21 101 501)
count=5
seed_counter=1

for n in "${sizes[@]}"; do
    echo "--- $n x $n boyutunda labirentler üretiliyor ---"
    for i in $(seq 1 $count); do
        filename="test_cases/maze_${n}_v${i}.txt"
        
        # C programını çalıştır ve çıktısını kontrol et
        ./maze_gen $n $filename $seed_counter
        
        # Eğer program başarılı çalıştıysa (exit code 0)
        if [ $? -eq 0 ]; then
            echo "Basarili: $filename (Seed: $seed_counter)"
        else
            echo "HATA: $filename üretilemedi!"
        fi
        
        ((seed_counter++))
    done
done