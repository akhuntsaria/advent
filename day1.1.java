import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

class Day1 {
    public static void main(String[] args) throws FileNotFoundException {
        File txt = new File("input1.1.txt");
        try (Scanner scan = new Scanner(txt)) {
            var l1 = new ArrayList<Integer>();
            var l2 = new ArrayList<Integer>();
            while (scan.hasNextInt()) {
                String[] input = scan.nextLine().split("   ", 2);
                l1.add(Integer.parseInt(input[0]));
                l2.add(Integer.parseInt(input[1]));
            }
            Collections.sort(l1);
            Collections.sort(l2);
            var res = 0l;
            for (int i = 0;i < l1.size();i++) {
                res += Math.abs(l1.get(i) - l2.get(i));
            }

            System.out.println(res);
        }
    }   
}