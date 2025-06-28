import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.ArrayList;

class PilhaDinamica {
    private ArrayList<Float> pilha;

    public PilhaDinamica() {
        this.pilha = new ArrayList<>();
    }

    public void empilhar(float elemento) {
        pilha.add(elemento);
    }

    public float desempilhar() {
        if (!pilha.isEmpty()) {
            return pilha.remove(pilha.size() - 1);
        }
        throw new RuntimeException("Pilha vazia");
    }

    public float topo() {
        if (!pilha.isEmpty()) {
            return pilha.get(pilha.size() - 1);
        }
        throw new RuntimeException("Pilha vazia");
    }

    public boolean vazia() {
        return pilha.isEmpty();
    }

    public int tamanho() {
        return pilha.size();
    }

    public void limpar() {
        pilha.clear();
    }

    public float[] toArray() {
        float[] array = new float[pilha.size()];
        for (int i = 0; i < pilha.size(); i++) {
            array[i] = pilha.get(i);
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
        if (indice >= 0 && indice < pilha.size()) {
            return pilha.get(indice);
        }
        throw new IndexOutOfBoundsException("Índice inválido");
    }
}

public class MergeSortPilhaDinamica{
    public static void main(String[] args){
        int[] tamanhos = {100, 1000, 10000, 100000, 1000000};
        
        try(BufferedWriter csvWriter = new BufferedWriter(new FileWriter("/home/siratuti/AEDS/testeJava/Java/data/Output/resultsJava.csv", true))){
            // Se o arquivo estiver vazio, escreva o cabeçalho
            java.io.File file = new java.io.File("/home/siratuti/AEDS/testeJava/Java/data/Output/output.dat");
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
                    PilhaDinamica ratingsPilha = new PilhaDinamica();

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
                
                csvWriter.write(String.format("%d,pilha,dinamica,%.6f,%d\n", tamanho, avgTime, avgMemory));
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