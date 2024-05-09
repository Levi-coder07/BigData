import random
import string

def generate_random_string(length):
    return ''.join(random.choices(string.ascii_lowercase, k=length))

file_size_gb = 0.8
file_size_bytes = file_size_gb * (1024 ** 3)  # Convertir de GB a bytes
words_per_gb = int(file_size_bytes // 5)  # Suponiendo que cada palabra tenga 5 bytes (4 letras + 1 byte de salto de línea)
for i in range(3,10):
    with open(f"t{i}.txt", "w") as file:
        for _ in range(words_per_gb):
            file.write(generate_random_string(4) + "\n")
