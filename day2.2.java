import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Day2 {
    public static void main(String[] args) throws FileNotFoundException {
        File txt = new File("input2.2.txt");
        try (Scanner scan = new Scanner(txt)) {
            var safe = 0;
            while (scan.hasNextLine()) {
                String[] line = scan.nextLine().split(" ");
                var l = new ArrayList<Integer>();
                for (var strNum : line) {
                    l.add(Integer.parseInt(strNum));
                }
                if (inc(l) || dec(l)) safe++;
                // if (inc(l) || dec(l)) {
                //      System.out.println(l);
                // }
            }
            System.out.println(safe);
        }
    }   

    private static boolean inc(List<Integer> org) {
        for (int skip = 0;skip < org.size();skip++) {
            var l = new ArrayList<>(org);
            l.remove(skip);
            //System.out.println(org + ", skip " + skip + " => " + l);
            var res = true;
            for (int i = 1;i < l.size();i++) {
                if (l.get(i-1) >= l.get(i) || l.get(i) - l.get(i-1) > 3) {
                    res = false;
                    break;
                }
            }
            if (res) return true;
        }
        return false;
    }

    private static boolean dec(List<Integer> org) {
        for (int skip = 0;skip < org.size();skip++) {
            var l = new ArrayList<>(org);
            l.remove(skip);
            //System.out.println(org + ", skip " + skip + " => " + l);
            var res = true;
            for (int i = 1;i < l.size();i++) {
                if (l.get(i-1) <= l.get(i) || l.get(i-1) - l.get(i) > 3) {
                    res = false;
                    break;
                }
            }
            if (res) return true;
        }
        return false;
    }
}
/*
 * 1 7 3 4 5
 */