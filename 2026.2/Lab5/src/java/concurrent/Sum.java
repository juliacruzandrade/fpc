import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Sum {

    public static int sum(FileInputStream fis) throws IOException {
        
	int byteRead;
        int sum = 0;
        
        while ((byteRead = fis.read()) != -1) {
        	sum += byteRead;
        }

        return sum;
    }

    public static long sum(String path) throws Exception {
        Thread.sleep(1000); // emulating an additional delay of 1 second
        Path filePath = Paths.get(path);
        if (Files.isRegularFile(filePath)) {
       	    FileInputStream fis = new FileInputStream(filePath.toString());
            return sum(fis);
        } else {
            throw new RuntimeException("Non-regular file: " + path);
        }
    }

    public static void main(String[] args) throws Exception {

        if (args.length < 1) {
            System.err.println("Usage: java Sum filepath1 filepath2 filepathN");
            System.exit(1);
        }

	//many exceptions could be thrown here. we don't care

        Thread[] threads = new Thread[args.length];

        int i = 0;
        for (String path : args) {
            Thread t = new Thread(new Work(path));
            threads[i] = t;
            i++;
            t.start();
        }

        for (Thread t : threads) {
            t.join();
        }

    }
}

class Work implements Runnable {
    public String path;
    public long sum = 0;

    public Work(String path) {
        this.path = path;
    }

    @Override
    public void run() {
        try {
            this.sum = Sum.sum(path);
            System.out.println(path + " : " + sum);
        } catch (Exception e) {
            System.err.println("erro");
        }
    }
}