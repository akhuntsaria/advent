import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Solution {
    public static void main(String[] args) throws FileNotFoundException {
        File txt = new File("input6.2.txt");
        var map = new ArrayList<char[]>();
        int i = -1, j = -1;
        try (Scanner scan = new Scanner(txt)) {
            var k = 0;
            while (scan.hasNextLine()) {
                var line = scan.nextLine();
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
        var res = 0;
        for (int k = 0;k < map.size();k++) {
            for (int l = 0;l < map.get(k).length;l++) {
                var c = map.get(k)[l];
                if (c == '#') {
                    continue;
                }
                map.get(k)[l] = '#';
                if (isLooped(map, new int[map.size()][map.get(k).length], i, j)) {
                    System.out.println(k + " " + l);
                    res++;
                }
                map.get(k)[l] = '.';
            }
        }
        System.out.println(res);
    }

    private static boolean isLooped(List<char[]> map, int[][] visited, int i, int j) {
        int dir = 1;
        while (true) {
            if (visited[i][j] == dir) { // Been here with the same direction == loop
                return true;
            }
            visited[i][j] = dir;
            for (int ndir = dir;;ndir++) {// keep rotating
                if (ndir > 4) ndir = 1;
                if (ndir == 1) {
                    if (i == 0) {
                        return false;
                    }
                    if (map.get(i-1)[j] == '#') {
                        continue;
                    }
                    i--;
                } else if (ndir == 2) {
                    if (j == map.get(i).length - 1) {
                        return false;
                    }
                    if (map.get(i)[j+1] == '#') {
                        continue;
                    }
                    j++;
                } else if (ndir == 3) {
                    if (i == map.size() - 1) {
                        return false;
                    }
                    if (map.get(i+1)[j] == '#') {
                        continue;
                    }
                    i++;
                } else {// 4
                    if (j == 0) {
                        return false;
                    }
                    if (map.get(i)[j-1] == '#') {
                        continue;
                    }
                    j--;
                }
                dir = ndir;
                break;
            }
        }
    }
}
