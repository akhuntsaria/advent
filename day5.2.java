import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;

class Day5 {
    public static void main(String[] args) throws FileNotFoundException {
        File txt = new File("input5.2.txt");
        var order = new HashMap<Integer, Set<Integer>>();
        var sum = 0;
        try (Scanner scan = new Scanner(txt)) {
            while (scan.hasNextLine()) {
                var line = scan.nextLine();
                if (line.contains("|")) {
                    var parts = line.split("\\|");
                    int n1 = Integer.parseInt(parts[0]),
                        n2 = Integer.parseInt(parts[1]);
                    var orderSet = order.get(n1);
                    if (orderSet == null) {
                        orderSet = new HashSet<Integer>();
                        order.put(n1, orderSet);
                    }
                    orderSet.add(n2);
                } else if (line.isEmpty()) {
                    continue;
                } else {
                    var parts = line.split(",");
                    var l = new ArrayList<Integer>();
                    for (var part : parts) {
                        l.add(Integer.parseInt(part));
                    }

                    var correct = true;
                    for (int i = 1;i < l.size();i++) {
                        if (order.get(l.get(i)) != null && order.get(l.get(i)).contains(l.get(i-1))) {
                            correct = false;
                            break;
                        }
                    }
                    if (!correct) {
                        Collections.sort(l, (a, b) -> {
                            if (order.get(a) != null && order.get(a).contains(b)) {
                                return -1;
                            }
                            if (order.get(b) != null && order.get(b).contains(a)) {
                                return 1;
                            }
                            return 0;
                        });
                        sum += l.get(l.size() / 2); 
                    }
                }
            }
        }
        System.out.println(sum);
    }
}
/*

 */