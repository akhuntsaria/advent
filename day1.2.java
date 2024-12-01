import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

class Day1 {
    public static void main(String[] args) throws FileNotFoundException {
        File txt = new File("input1.1.txt");
        try (Scanner scan = new Scanner(txt)) {
            var l1 = new ArrayList<Integer>();
            var m2 = new HashMap<Integer, Integer>();
            while (scan.hasNextInt()) {
                String[] input = scan.nextLine().split("   ", 2);
                l1.add(Integer.parseInt(input[0]));

                var n2 = Integer.parseInt(input[1]);
                
                m2.merge(n2, 1, Integer::sum);
            }
            var res = 0l;
            for (int i = 0;i < l1.size();i++) {
                res += l1.get(i) * m2.getOrDefault(l1.get(i), 0);
            }

            System.out.println(res);
        }
    }   
}