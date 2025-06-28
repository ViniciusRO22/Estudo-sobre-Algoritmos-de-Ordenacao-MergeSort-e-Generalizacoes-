import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;

class ListaLinear {
    private float[] elementos;
    private int tamanho;
    private int capacidade;

    public ListaLinear(int capacidade) {
        this.capacidade = capacidade;
        this.elementos = new float[capacidade];
        this.tamanho = 0;
    }

    public void adicionar(float elemento) {
        if (tamanho < capacidade) {
            elementos[tamanho] = elemento;
            tamanho++;
        }
    }

    public float get(int indice) {
        if (indice >= 0 && indice < tamanho) {
            return elementos[indice];
        }
        throw new IndexOutOfBoundsException("Índice inválido");
    }

    public void set(int indice, float elemento) {
        if (indice >= 0 && indice < tamanho) {
            elementos[indice] = elemento;
        }
    }

    public int tamanho() {
        return tamanho;
    }

    public void limpar() {
        tamanho = 0;
    }

    public float[] toArray() {
        float[] array = new float[tamanho];
        for (int i = 0; i < tamanho; i++) {
            array[i] = elementos[i];
        }
        return array;
    }

    public void fromArray(float[] array) {
        limpar();
        for (float elemento : array) {
            adicionar(elemento);
        }
    }
}

public class MergeSortListaLinear{
    public static void main(String[] args){
        int[] tamanhos = {100, 1000, 10000, 100000, 1000000};
        
        try(BufferedWriter csvWriter = new BufferedWriter(new FileWriter("/home/siratuti/AEDS/testeJava/Java/data/Output/output.dat", true))){
            //csvWriter.write("size,structure,representation,duration_s,mem_bytes\n");
            
            for(int t = 0; t < tamanhos.length; t++){
                double allTimes = 0;
                long totalMemory = 0;
                int tamanho = tamanhos[t];
                
                for(int i = 0; i < 10; i++){
                    System.gc();
                    Runtime runtime = Runtime.getRuntime();
                    long memoryBefore = runtime.totalMemory() - runtime.freeMemory();
                    
                    long startTime = System.nanoTime();
                    String csvFile = "/home/siratuti/AEDS/testeJava/Java/data/Input/ratings.csv";
                    ListaLinear ratingsLista = new ListaLinear(tamanho);

                    try(BufferedReader br = new BufferedReader(new FileReader(csvFile))){
                        String line;
                        br.readLine(); 

                        while((line = br.readLine()) != null && ratingsLista.tamanho() < tamanho){
                            String[] parts = line.split(",");
                            
                            if(parts.length >= 3){
                                try{
                                    ratingsLista.adicionar(Float.parseFloat(parts[2])); 
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

                    float[] ratingsArray = ratingsLista.toArray();

                    ratingsArray = mergeSort(ratingsArray);

                    ratingsLista.fromArray(ratingsArray);

                    try(BufferedWriter writer = new BufferedWriter(new FileWriter("/home/siratuti/AEDS/testeJava/Java/data/Output/output.dat"))){
                        writer.write("Ratings ordenados:\n");
                        for(int j = 0; j < ratingsLista.tamanho(); j++) {
                            writer.write(String.valueOf(ratingsLista.get(j)));
                            writer.newLine();
                        }
                    }
                    catch (IOException e){
                        System.err.println("Erro ao escrever no arquivo:");
                        e.printStackTrace();
                    }
                    
                    long endTime = System.nanoTime();
                    long memoryAfter = runtime.totalMemory() - runtime.freeMemory();
                    
                    double durationInSeconds = (endTime - startTime) / 1_000_000_000.0;
                    long memoryUsed = memoryAfter - memoryBefore;
                    
                    allTimes += durationInSeconds;
                    totalMemory += memoryUsed;
                }
                
                double averageTime = allTimes / 10;
                long averageMemory = totalMemory / 10;
                
                csvWriter.write(String.format("%d,lista,linear,%.6f,%d%n", 
                    tamanho, averageTime, averageMemory));
            }
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