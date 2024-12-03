import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;
import java.util.regex.Pattern;

class Day3 {
    public static void main(String[] args) throws IOException {
        var content = new String(Files.readAllBytes(Paths.get("input3.2.txt")), StandardCharsets.UTF_8);
        var dontIdx = content.indexOf("don't()");
        if (dontIdx == -1) {
            dontIdx = content.length();
        }
        System.out.println("Don't: " + dontIdx);
        var sum = calc(content.substring(0, dontIdx));
        while (true) {
            if (dontIdx == content.length()) {
                break;
            }
            var doIdx = content.indexOf("do()", dontIdx + 7);
            if (doIdx == -1) {
                break;
            }
            dontIdx = content.indexOf("don't()", doIdx + 4);
            if (dontIdx == -1) {
                dontIdx = content.length();
            }
            sum += calc(content.substring(doIdx, dontIdx));
        }
        System.out.println(sum);
    }   

    private static long calc(String txt) {
        var sum = 0l;
        var pattern = Pattern.compile("mul\\((\\d+),(\\d+)\\)", Pattern.MULTILINE);
        var matcher = pattern.matcher(txt);
        while (matcher.find()) {
            long n1 = Long.parseLong(matcher.group(1)),
                n2 = Long.parseLong(matcher.group(2));
            sum += n1 * n2;
        }
        return sum;
    }
}