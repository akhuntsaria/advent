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
        for (int i = 2;i < lines.size();i++) {
            for (int j = 2;j < lines.get(i).length();j++) {
                var sb = new StringBuilder();
                sb.append(lines.get(i).charAt(j));
                sb.append(lines.get(i-1).charAt(j-1));
                sb.append(lines.get(i-2).charAt(j-2));
                var s = sb.toString();
                if (!s.equals("MAS") && !s.equals("SAM")) {
                    continue;
                }
                sb = new StringBuilder();
                sb.append(lines.get(i).charAt(j-2));
                sb.append(lines.get(i-1).charAt(j-1));
                sb.append(lines.get(i-2).charAt(j));
                s = sb.toString();
                if (s.equals("MAS") || s.equals("SAM")) {
                    count++;
                }
            }
        }
        System.out.println(count);
    }
}
/*

 */