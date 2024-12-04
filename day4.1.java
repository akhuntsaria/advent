import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Pattern;

class Day4 {
    public static void main(String[] args) throws FileNotFoundException {
        var count = 0;
        File txt = new File("input4.2.txt");
        var lines = new ArrayList<String>();
        try (Scanner scan = new Scanner(txt)) {
            while (scan.hasNextLine()) {
                lines.add(scan.nextLine());
            }
        }
        count += horizontal(lines);
        System.out.println("Horizontal: " + count);
        count += vertical(lines);
        System.out.println("Vertical: " + count);
        count += diagonal(lines);
        System.out.println("Diagonal 1: " + count);

        var reversed = new ArrayList<String>();
        for (int i = 0;i < lines.size();i++) {
            reversed.add(new StringBuilder(lines.get(i)).reverse().toString());
        }
        count += diagonal(reversed);
        //horizontal(List.of("XMASXMASXMASSAMX"));
        System.out.println(count);
    }

    private static int horizontal(List<String> lines) throws FileNotFoundException {
        var count = 0;
        for (var line : lines) {
            for (int i = 3;i < line.length();i++) {
                var s = line.substring(i-3, i+1);
                if (s.equals("XMAS") || s.equals("SAMX")) {
                    count++;
                }
            }
        }
        return count;
    }

    private static int vertical(List<String> lines) throws FileNotFoundException {
        var count = 0;
        for (int j = 0;j < lines.get(0).length();j++) {
            for (int i = 3;i < lines.size();i++) {
                var sb = new StringBuilder();
                sb.append(lines.get(i-3).charAt(j));
                sb.append(lines.get(i-2).charAt(j));
                sb.append(lines.get(i-1).charAt(j));
                sb.append(lines.get(i).charAt(j));
                var s = sb.toString();
                if (s.equals("XMAS") || s.equals("SAMX")) {
                    count++;
                }
            }
        }
        return count;
    }

    private static int diagonal(List<String> lines) throws FileNotFoundException {
        var count = 0;
        // From any point into the top-left corner
        for (int i = 3;i < lines.size();i++) {
            for (int j = 3; j < lines.get(i).length(); j++) {
                var sb = new StringBuilder();
                sb.append(lines.get(i).charAt(j));
                sb.append(lines.get(i-1).charAt(j-1));
                sb.append(lines.get(i-2).charAt(j-2));
                sb.append(lines.get(i-3).charAt(j-3));
                var s = sb.toString();
                if (s.equals("XMAS") || s.equals("SAMX")) {
                    count++;
                    System.out.println("Diagonal at " + i + "," + j);
                }
            }
        }
        return count;
    }
}
/*

 */