import java.util.*;

class Solution {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int min, n = in.nextInt();

        if (n > 0)
        {
            min = in.nextInt();
            for (int i = 0; i < n - 1; i++)
            {
                int t = in.nextInt();

                System.err.printf("%d %d\n", min, t);
                if (Math.abs(min) - Math.abs(t) == 0 && min < 0 && t > 0)
                    min = t;
                if (Math.abs(t) < Math.abs(min))
                    min = t;           
            }
        }
        else min = 0;

        System.out.printf("%d\n", min);
        in.close();
    }
}