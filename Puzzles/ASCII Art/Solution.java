import java.util.*;

class Solution 
{
    static int L;
    static int H;
    static int SIZE;

    static String ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ?";

    public static void parse(ArrayList<String[]> letters, String ROW, int i)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int start = j * L;
            int end = Math.min(start + L, ROW.length() - 1);
            String substring = ROW.substring(start, end);
            letters.get(j)[i] = substring;
        }
    }

    public static void main(String args[])
    {
        Scanner in = new Scanner(System.in);
        L = in.nextInt();
        H = in.nextInt();

        if (in.hasNextLine())
            in.nextLine();
        String T = in.nextLine();

        ArrayList<String[]> letters = new ArrayList<String[]>();
        
        String ROW = in.nextLine();
        SIZE = (int) Math.floor(ROW.length() / L);
        
        for (int j = 0; j < SIZE; j++)
            letters.add(new String[H]);

        parse(letters, ROW, 0);
        for (int i = 1; i < H; i++)
        {
            ROW = in.nextLine();
            parse(letters, ROW, i);
        }

        for (int j = 0; j < H; j++)
        {
            String result = "";
            for (int i = 0; i < T.length(); i++)
            {
                char c = T.toUpperCase().charAt(i);
                boolean contains = ALPHA.contains("" + c);
                int ASCII = contains ? ALPHA.indexOf(c) : ALPHA.length() - 1;
                result += letters.get(ASCII)[j];
                if (!contains) result += " ";
            }
            System.out.println(result);
        }
    }
}