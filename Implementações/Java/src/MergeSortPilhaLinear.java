import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;

class PilhaLinear {
    private float[] pilha;
    private int topo;
    private int capacidade;

    public PilhaLinear(int capacidade) {
        this.capacidade = capacidade;
        this.pilha = new float[capacidade];
        this.topo = -1;
    }

    public void empilhar(float elemento) {
        if (topo < capacidade - 1) {
            pilha[++topo] = elemento;
        }
    }

    public float desempilhar() {
        if (topo >= 0) {
            return pilha[topo--];
        }
        throw new RuntimeException("Pilha vazia");
    }

    public float consultarTopo() {
        if (topo >= 0) {
            return pilha[topo];
        }
        throw new RuntimeException("Pilha vazia");
    }

    public boolean vazia() {
        return topo == -1;
    }

    public boolean cheia() {
        return topo == capacidade - 1;
    }

    public int tamanho() {
        return topo + 1;
    }

    public void limpar() {
        topo = -1;
    }

    public float[] toArray() {
        float[] array = new float[tamanho()];
        for (int i = 0; i < tamanho(); i++) {
            array[i] = pilha[i];
        }
        return array;
    }

    public void fromArray(float[] array) {
        limpar();
        for (float elemento : array) {
            empilhar(elemento);
        }
    }

    public float get(int indice) {
        if (indice >= 0 && indice < tamanho()) {
            return pilha[indice];
        }
        throw new IndexOutOfBoundsException("Índice inválido");
    }
}

public class MergeSortPilhaLinear{
    public static void main(String[] args){
        int[] tamanhos = {100, 1000, 10000, 100000, 1000000};
        
        try {
            File file = new File("/home/siratuti/AEDS/testeJava/Java/data/Output/output.dat");
            boolean append = true;
            BufferedWriter csvWriter = new BufferedWriter(new FileWriter(file, append));
            if (file.length() == 0) {
                csvWriter.write("size,structure,representation,duration_s,mem_bytes\n");
            }
            
            for(int t = 0; t < tamanhos.length; t++){
                double allTimes = 0;
                long totalMemory = 0;
                int tamanho = tamanhos[t];
                
                for(int i = 0; i < 10; i++){
                    Runtime.getRuntime().gc();
                    long memBefore = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
                    
                    long startTime = System.nanoTime();
                    String csvFile = "/home/siratuti/AEDS/testeJava/Java/data/Input/ratings.csv";
                    PilhaLinear ratingsPilha = new PilhaLinear(tamanho);

                    try(BufferedReader br = new BufferedReader(new FileReader(csvFile))){
                        String line;
                        br.readLine(); 

                        while((line = br.readLine()) != null && ratingsPilha.tamanho() < tamanho){
                            String[] parts = line.split(",");
                            
                            if(parts.length >= 3){
                                try{
                                    ratingsPilha.empilhar(Float.parseFloat(parts[2])); 
                                } 
                                catch(NumberFormatException e){
                                    continue;
                                }
                            }
                        }
                    }
                    catch(IOException e){
                        e.printStackTrace();
                    }

                    float[] ratingsArray = ratingsPilha.toArray();
                    ratingsArray = mergeSort(ratingsArray);
                    ratingsPilha.fromArray(ratingsArray);

                    try(BufferedWriter writer = new BufferedWriter(new FileWriter("/home/siratuti/AEDS/testeJava/Java/data/Output/output.dat"))){
                        writer.write("Ratings ordenados:\n");
                        for(int j = 0; j < ratingsPilha.tamanho(); j++) {
                            writer.write(String.valueOf(ratingsPilha.get(j)));
                            writer.newLine();
                        }
                    }
                    catch (IOException e){
                        System.err.println("Erro ao escrever no arquivo:");
                        e.printStackTrace();
                    }
                    
                    long endTime = System.nanoTime();
                    long memAfter = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
                    
                    double durationInSeconds = (endTime - startTime) / 1_000_000_000.0;
                    allTimes += durationInSeconds;
                    totalMemory += (memAfter - memBefore);
                }
                
                double avgTime = allTimes / 10;
                long avgMemory = totalMemory / 10;
                
                csvWriter.write(String.format("%d,pilha,linear,%.6f,%d\n", tamanho, avgTime, avgMemory));
            }
            csvWriter.close();
        }
        catch(IOException e){
            e.printStackTrace();
        }
    }

    static float[] mergeSort(float[] arr){
        if (arr.length <= 1) return arr;

        int mid = arr.length / 2;

        float[] left = mergeSort(Arrays.copyOfRange(arr, 0, mid));
        float[] right = mergeSort(Arrays.copyOfRange(arr, mid, arr.length));

        return merge(left, right);
    }

    private static float[] merge(float[] left, float[] right){
        float[] merged = new float[left.length + right.length];
        int i = 0, j = 0, k = 0;

        while(i < left.length && j < right.length){
            if(left[i] < right[j]){
                merged[k++] = left[i++];
            }
            else{
                merged[k++] = right[j++];
            }
        }

        while(i < left.length){
            merged[k++] = left[i++];
        }

        while(j < right.length){
            merged[k++] = right[j++];
        }

        return merged;
    }
}