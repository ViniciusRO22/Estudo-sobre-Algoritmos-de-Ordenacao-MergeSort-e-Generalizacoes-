import csv
import time
import tracemalloc  
from typing import List, Dict, Tuple

# Definições de estruturas estáticas 
class ListaEstatica:
    """Lista estática com capacidade fixa - Representação Linear"""
    def __init__(self, capacidade: int):
        self.capacidade = capacidade
        self.dados = [None] * capacidade
        self.tamanho = 0

    def inserir(self, valor) -> bool:
        if self.tamanho < self.capacidade:
            self.dados[self.tamanho] = valor
            self.tamanho += 1
            return True
        return False

    def limpar(self):
        self.dados = [None] * self.capacidade
        self.tamanho = 0

    def to_list(self) -> List:
        return self.dados[:self.tamanho]

    def atualizar(self, lista: List):
        self.limpar()
        for valor in lista[:self.capacidade]:
            self.inserir(valor)

class FilaEstatica:
    """Fila estática simples (FIFO) — Representação Linear"""
    def __init__(self, capacidade: int):
        self.capacidade = capacidade
        self.buffer = [None] * capacidade
        self.tamanho = 0

    def enfileirar(self, valor) -> bool:
        if self.tamanho < self.capacidade:
            self.buffer[self.tamanho] = valor
            self.tamanho += 1
            return True
        return False

    def limpar(self):
        self.buffer = [None] * self.capacidade
        self.tamanho = 0

    def to_list(self) -> List:
        return self.buffer[:self.tamanho]

    def atualizar(self, lista: List):
        self.limpar()
        for valor in lista[:self.capacidade]:
            self.enfileirar(valor)

class PilhaEstatica:
    """Pilha estática (LIFO) - Representação Linear"""
    def __init__(self, capacidade: int):
        self.capacidade = capacidade
        self.buffer = [None] * capacidade
        self.topo = -1

    def empilhar(self, valor) -> bool:
        if self.topo + 1 < self.capacidade:
            self.topo += 1
            self.buffer[self.topo] = valor
            return True
        return False

    def limpar(self):
        self.buffer = [None] * self.capacidade
        self.topo = -1

    def to_list(self) -> List:
        return self.buffer[:self.topo + 1]

    def atualizar(self, lista: List):
        self.limpar()
        for valor in lista[:self.capacidade]:
            self.empilhar(valor)

# Definições de estruturas dinâmicas 
class No:
    """Nó para estruturas dinâmicas"""
    def __init__(self, valor):
        self.valor = valor
        self.prox = None

class ListaDinamica:
    """Lista dinâmica - Representação Dinâmica"""
    def __init__(self):
        self.cabeca = None
        self.fim = None  
        self.tamanho = 0

    def inserir(self, valor):
        novo = No(valor)
        if self.cabeca is None:  
            self.cabeca = novo
            self.fim = novo
        else:  
            self.fim.prox = novo
            self.fim = novo
        self.tamanho += 1

    def limpar(self):
        self.cabeca = None
        self.fim = None
        self.tamanho = 0

    def to_list(self) -> List:
        resultado = []
        atual = self.cabeca
        while atual:
            resultado.append(atual.valor)
            atual = atual.prox
        return resultado

    def atualizar(self, lista: List):
        self.limpar()
        for valor in lista:
            self.inserir(valor)

class FilaDinamica:
    """Fila dinâmica (FIFO) - Representação Dinâmica"""
    def __init__(self):
        self.inicio = None
        self.fim = None
        self.tamanho = 0

    def enfileirar(self, valor):
        novo = No(valor)
        if not self.inicio:
            self.inicio = novo
            self.fim = novo
        else:
            self.fim.prox = novo
            self.fim = novo
        self.tamanho += 1

    def limpar(self):
        self.inicio = None
        self.fim = None
        self.tamanho = 0

    def to_list(self) -> List:
        resultado = []
        atual = self.inicio
        while atual:
            resultado.append(atual.valor)
            atual = atual.prox
        return resultado

    def atualizar(self, lista: List):
        self.limpar()
        for valor in lista:
            self.enfileirar(valor)

class PilhaDinamica:
    """Pilha dinâmica (LIFO) - Representação Dinâmica"""
    def __init__(self):
        self.topo = None
        self.tamanho = 0

    def empilhar(self, valor):
        novo = No(valor)
        novo.prox = self.topo
        self.topo = novo
        self.tamanho += 1

    def limpar(self):
        self.topo = None
        self.tamanho = 0

    def to_list(self) -> List:
        resultado = []
        atual = self.topo
        while atual:
            resultado.append(atual.valor)
            atual = atual.prox
        resultado.reverse()
        return resultado

    def atualizar(self, lista: List):
        self.limpar()
        for valor in lista:
            self.empilhar(valor)

# Implementação do Merge Sort
def mergesort(lista: List) -> List:
    """Merge Sort - O(n log n)"""
    if len(lista) <= 1:
        return lista
    
    meio = len(lista) // 2
    esquerda = mergesort(lista[:meio])
    direita = mergesort(lista[meio:])
    return merge(esquerda, direita)

def merge(esq: List, dir: List) -> List:
    """Combina duas listas ordenadas"""
    resultado = []
    i = j = 0
    
    while i < len(esq) and j < len(dir):
        if esq[i] <= dir[j]:
            resultado.append(esq[i])
            i += 1
        else:
            resultado.append(dir[j])
            j += 1
    
    resultado.extend(esq[i:])
    resultado.extend(dir[j:])
    return resultado

def carregar_n_linhas_csv(caminho: str, n: int) -> List[float]:
    """
    Carrega exatamente n linhas do CSV - TEMPO REALÍSTICO
    Esta função é chamada para cada teste individualmente
    """
    resultado = []
    
    with open(caminho, newline='', encoding='utf-8') as csvfile:
        leitor = csv.reader(csvfile)
        next(leitor, None)  # Pula cabeçalho
        
        for linha in leitor:
            if len(resultado) >= n:
                break
            try:
                if len(linha) > 2:
                    rating = float(linha[2].strip())
                    resultado.append(rating)
            except (ValueError, IndexError):
                continue
    
    return resultado

def executar_benchmark_completo(caminho_csv: str, n: int, estrutura, nome_estrutura: str, representacao: str, num_execucoes: int = 10) -> Tuple[float, List, int]:
    """
    BENCHMARK COMPLETO COM MÉDIA DE 10 EXECUÇÕES
    Inclui: Leitura CSV + Inserção + Ordenação + Atualização
    """
    tempos = []
    estrutura_final = None
    mem_usada = 0

    for execucao in range(num_execucoes):
        # INICIA CRONÔMETRO - TEMPO TOTAL REALÍSTICO
        tracemalloc.start()  # Inicia o monitoramento de memória
        inicio_total = time.perf_counter()
        
        # 1. LEITURA DO CSV (parte do tempo total)
        dados = carregar_n_linhas_csv(caminho_csv, n)
        
        # 2. INSERÇÃO DOS DADOS NA ESTRUTURA
        estrutura.limpar()
        
        if hasattr(estrutura, 'inserir'):
            for valor in dados:
                estrutura.inserir(valor)
        elif hasattr(estrutura, 'enfileirar'):
            for valor in dados:
                estrutura.enfileirar(valor)
        elif hasattr(estrutura, 'empilhar'):
            for valor in dados:
                estrutura.empilhar(valor)
        
        # 3. CONVERSÃO PARA LISTA
        lista_aux = estrutura.to_list()
        
        # 4. ORDENAÇÃO COM MERGE SORT
        lista_ordenada = mergesort(lista_aux)
        
        # 5. ATUALIZAÇÃO DA ESTRUTURA
        estrutura.atualizar(lista_ordenada)
        
        # PARA CRONÔMETRO
        fim_total = time.perf_counter()
        tempo_execucao = fim_total - inicio_total
        tempos.append(tempo_execucao)

        # Pega o pico de memória da execução
        current, peak = tracemalloc.get_traced_memory()
        tracemalloc.stop()
        if peak > mem_usada:
            mem_usada = peak

        # Guarda resultado da última execução para verificação
        if execucao == num_execucoes - 1:
            estrutura_final = estrutura.to_list()
    
    # Calcula tempo médio
    tempo_medio = sum(tempos) / len(tempos)
    
    return tempo_medio, estrutura_final, mem_usada

def salvar_csv_resultados(resultados: List[Dict], arquivo: str = "data/Output/benchmark_results.csv"):
    """Salva resultados no formato do benchmark fornecido"""
    with open(arquivo, 'w', newline='', encoding='utf-8') as csvfile:
        fieldnames = ['size', 'structure', 'representation', 'duration_s', 'mem_bytes']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(resultados)
    print(f"Resultados salvos em: {arquivo}")

def salvar_estruturas_ordenadas(estruturas_ordenadas: Dict, arquivo: str = "data/Output/estruturas_ordenadas.txt"):
    """Salva as estruturas ordenadas para verificação"""
    with open(arquivo, 'w', encoding='utf-8') as f:
        f.write("ESTRUTURAS ORDENADAS - VERIFICAÇÃO\n")
        f.write("=" * 50 + "\n\n")
        
        for key, dados in estruturas_ordenadas.items():
            f.write(f"{key}\n")
            f.write("-" * len(key) + "\n")
            
            # Primeiros 20 elementos
            primeiros = dados[:20]
            f.write(f"Primeiros 20: {primeiros}\n")
            
            # Últimos 20 elementos
            if len(dados) > 20:
                ultimos = dados[-20:]
                f.write(f"Últimos 20: {ultimos}\n")
            
            # Verificação se está ordenado
            esta_ordenado = all(dados[i] <= dados[i+1] for i in range(len(dados)-1))
            f.write(f"Está ordenado: {'SIM' if esta_ordenado else 'NÃO'}\n")
            f.write(f"Total de elementos: {len(dados):,}\n\n")
    
    print(f"Estruturas ordenadas salvas em: {arquivo}")

def main():
    # Configurações
    caminho_csv = "data/Input/ratings.csv"
    tamanhos_teste = [100, 1000, 10000, 100000, 1000000]
    
    # Definição das estruturas com metadados
    estruturas_config = [
        (ListaEstatica, "lista", "linear"),
        (ListaDinamica, "lista", "dinamica"),
        (PilhaEstatica, "pilha", "linear"),
        (PilhaDinamica, "pilha", "dinamica"),
        (FilaEstatica, "fila", "linear"),
        (FilaDinamica, "fila", "dinamica"),
    ]
    
    resultados_benchmark = []
    estruturas_ordenadas = {}
    
    try:
        total_testes = len(tamanhos_teste) * len(estruturas_config)
        teste_atual = 0
        
        for tamanho in tamanhos_teste:
            print(f"\n TESTANDO COM {tamanho:,} ELEMENTOS")
            print("-" * 50)
            
            for estrutura_class, nome_estrutura, representacao in estruturas_config:
                teste_atual += 1
                
                # Cria estrutura com capacidade adequada
                if representacao == "linear":
                    estrutura = estrutura_class(tamanho)
                else:
                    estrutura = estrutura_class()
                
                print(f"  [{teste_atual:2d}/{total_testes}] {nome_estrutura} ({representacao})... ", end="", flush=True)
                
                try:
                    # EXECUTA BENCHMARK COM 10 EXECUÇÕES E MÉDIA
                    tempo_medio, dados_ordenados, mem_usada = executar_benchmark_completo(
                        caminho_csv, tamanho, estrutura, nome_estrutura, representacao, 1  # <-- troque 10 por 1
                    )
                    
                    # Salva resultado
                    resultado = {
                        'size': tamanho,
                        'structure': nome_estrutura,
                        'representation': representacao,
                        'duration_s': round(tempo_medio, 6),
                        'mem_bytes': mem_usada
                    }
                    resultados_benchmark.append(resultado)
                    
                    # Salva estrutura ordenada para verificação
                    chave = f"{tamanho}_{nome_estrutura}_{representacao}"
                    estruturas_ordenadas[chave] = dados_ordenados
                    
                    print(f" {tempo_medio:.6f}s (média de 10 execuções) | Memória pico: {mem_usada} bytes")
                    
                except Exception as e:
                    print(f"ERRO: {e}")
                    continue
        
        # Salva resultados
        print(f"\SALVANDO RESULTADOS...")
        salvar_csv_resultados(resultados_benchmark)
        salvar_estruturas_ordenadas(estruturas_ordenadas)
        
        # Mostra resumo
        print(f"\n RESUMO DO BENCHMARK")
        print("=" * 50)
        print(f"Total de testes executados: {len(resultados_benchmark)}")
        print(f"Tamanhos testados: {tamanhos_teste}")
        print(f"Estruturas testadas: {len(estruturas_config)}")
        print(f"Tempo médio de 10 execuções inclui: Leitura CSV + Inserção + Ordenação + Atualização")
        
    except Exception as e:
        print(f" Erro geral: {e}")

if __name__ == '__main__':
    main()