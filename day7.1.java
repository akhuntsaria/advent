import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Solution {
    public static void main(String[] args) throws FileNotFoundException {
        File txt = new File("input7.2.txt");
        var total = 0l;
        try (Scanner scan = new Scanner(txt)) {
            while (scan.hasNextLine()) {
                var line = scan.nextLine();
                total += processLine(line);
            }
        }
        System.out.println(total);
    }

    private static long processLine(String line) {
        var parts = line.split(":");
        var sum = Long.parseLong(parts[0]);
        var operands = new ArrayList<Long>();
        for (var operand : parts[1].split(" ")) {
            if (operand.isBlank()) continue;
            operands.add(Long.parseLong(operand));
        }
        return isValid(sum, operands, operands.get(0), 1) ? sum : 0;
    }

    private static boolean isValid(long targetSum, List<Long> operands, long currentSum, int i) {
        if (i == operands.size()) {
            return currentSum == targetSum;
        }
        if (currentSum > targetSum) return false;
        return isValid(targetSum, operands, currentSum + operands.get(i), i + 1) ||
             isValid(targetSum, operands, currentSum * operands.get(i), i + 1);
    }
}
