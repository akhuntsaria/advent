import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;

class Solution {
    public static void main(String[] args) throws FileNotFoundException {
        File txt = new File("input6.2.txt");
        var map = new ArrayList<char[]>();
        int i = -1, j = -1, 
            dir = 1; // (1-4, trbl)
        try (Scanner scan = new Scanner(txt)) {
            var k = 0;
            while (scan.hasNextLine()) {
                var line = scan.nextLine();
                //System.out.println(line);
                if (i == -1) {
                    var l = line.indexOf('^');
                    if (l != -1) {
                        i = k;
                        j = l;
                    }
                }
                map.add(line.toCharArray());
                k++;
            }
        }
        var visited = 0;
        while (true) {
            if (map.get(i)[j] == '.' || map.get(i)[j] == '^') {
                map.get(i)[j] = 'X';
                visited++;
            }
            if (dir == 1) {
                if (i == 0) {
                    break;
                }
                if (map.get(i-1)[j] == '#') {
                    if (j == map.get(i).length) {
                        break;
                    }
                    j++;
                    dir++;
                } else {
                    i--;
                }
            } else if (dir == 2) {
                if (j == map.get(i).length - 1) {
                    break;
                }
                if (map.get(i)[j+1] == '#') {
                    if (i == map.size() - 1) {
                        break;
                    }
                    i++;
                    dir++;
                } else {
                    j++;
                }
            } else if (dir == 3) {
                if (i == map.size() - 1) {
                    break;
                }
                if (map.get(i+1)[j] == '#') {
                    if (j == 0) {
                        break;
                    }
                    j--;
                    dir++;
                } else {
                    i++;
                }
            } else {// dir == 4
                if (j == 0) {
                    break;
                }
                if (map.get(i)[j-1] == '#') {
                    if (i == 0) {
                        break;
                    }
                    i--;
                    dir = 1;
                } else {
                    j--;
                }
            }
        }
        for (var line : map) {
            System.out.println(Arrays.toString(line));
        }
        System.out.println(visited);
    }
}
/*

 */