import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;

public class MergeSortFilaDinamica{
    public static void main(String[] args){
        int[] testSizes = {100, 1000, 10000, 100000, 1000000};
        
        try(BufferedWriter csvWriter = new BufferedWriter(new FileWriter("/home/siratuti/AEDS/testeJava/Java/data/Output/output.dat", true))){
            csvWriter.write("size,structure,representation,duration_s,mem_bytes\n");

            for(int sizeIndex = 0; sizeIndex < testSizes.length; sizeIndex++){
                int currentSize = testSizes[sizeIndex];
                double totalTime = 0;
                long totalMemory = 0;
                
                for(int i = 0; i < 10; i++){
                    System.gc();
                    Runtime runtime = Runtime.getRuntime();
                    long memoryBefore = runtime.totalMemory() - runtime.freeMemory();
                    
                    long startTime = System.nanoTime();
                    
                    String csvFile = "/home/siratuti/AEDS/testeJava/Java/data/Input/ratings.csv";
                    Queue<Float> ratingsQueue = new LinkedList<>();
                    int count = 0;

                    try(BufferedReader br = new BufferedReader(new FileReader(csvFile))){
                        String line;
                        br.readLine(); 

                        while((line = br.readLine()) != null && count < currentSize){
                            String[] parts = line.split(",");
                            if (parts.length >= 3) {
                                try{
                                    float rating = Float.parseFloat(parts[2]);
                                    ratingsQueue.add(rating);
                                    count++;
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

                    ratingsQueue = mergeSortWithArray(ratingsQueue);

                    try(BufferedWriter writer = new BufferedWriter(new FileWriter("/home/siratuti/AEDS/testeJava/Java/data/Output/output.dat"))){
                        writer.write("Ratings ordenados:\n");
                        while(!ratingsQueue.isEmpty()){
                            writer.write(String.valueOf(ratingsQueue.poll()));
                            writer.newLine();
                        }
                    } 
                    catch(IOException e){
                        System.err.println("Erro ao escrever no arquivo:");
                        e.printStackTrace();
                    }

                    long endTime = System.nanoTime();
                    long memoryAfter = runtime.totalMemory() - runtime.freeMemory();
                    
                    double durationInSeconds = (endTime - startTime) / 1_000_000_000.0;
                    long memoryUsed = memoryAfter - memoryBefore;
                    
                    totalTime += durationInSeconds;
                    totalMemory += memoryUsed;
                }
                
                double averageTime = totalTime / 10.0;
                long averageMemory = totalMemory / 10;
                
                String linha = String.format("%d,fila,dinamica,%.6f,%d%n", 
                    currentSize, averageTime, averageMemory);
                linha = linha.replaceFirst("(\\d+)\\.(\\d+)", "$1,$2");
                csvWriter.write(linha);
            }
        }
        catch(IOException e){
            e.printStackTrace();
        }
    }

    static Queue<Float> mergeSortWithArray(Queue<Float> queue){
        float[] array = new float[queue.size()];
        int index = 0;
        
        while(!queue.isEmpty()){
            array[index++] = queue.poll();
        }
        
        mergeSort(array, 0, array.length - 1);
        
        Queue<Float> sortedQueue = new LinkedList<>();
        for(float value : array){
            sortedQueue.add(value);
        }
        
        return sortedQueue;
    }
    
    static void mergeSort(float[] array, int left, int right){
        if(left < right){
            int mid = left + (right - left) / 2;
            
            mergeSort(array, left, mid);
            mergeSort(array, mid + 1, right);
            
            merge(array, left, mid, right);
        }
    }
    
    static void merge(float[] array, int left, int mid, int right){
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        float[] leftArray = new float[n1];
        float[] rightArray = new float[n2];
        
        for(int i = 0; i < n1; i++){
            leftArray[i] = array[left + i];
        }
        for(int j = 0; j < n2; j++){
            rightArray[j] = array[mid + 1 + j];
        }
        
        int i = 0, j = 0;
        int k = left;
        
        while(i < n1 && j < n2){
            if(leftArray[i] <= rightArray[j]){
                array[k] = leftArray[i];
                i++;
            } else {
                array[k] = rightArray[j];
                j++;
            }
            k++;
        }
        
        while(i < n1){
            array[k] = leftArray[i];
            i++;
            k++;
        }
        
        while(j < n2){
            array[k] = rightArray[j];
            j++;
            k++;
        }
    }
}