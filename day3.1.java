import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.regex.Pattern;

class Day3 {
    public static void main(String[] args) throws FileNotFoundException {
        File txt = new File("input3.2.txt");
        try (Scanner scan = new Scanner(txt)) {
            var sum = 0l;
            while (scan.hasNextLine()) {
                String line = scan.nextLine();
                System.out.println(line);

                var pattern = Pattern.compile("mul\\((\\d+),(\\d+)\\)");
                var matcher = pattern.matcher(line);
                while (matcher.find()) {
                    long n1 = Long.parseLong(matcher.group(1)),
                        n2 = Long.parseLong(matcher.group(2));
                    sum += n1 * n2;
                    System.out.println(n1 + " " + n2);
                }
            }
            System.out.println(sum);
        }
    }   
}