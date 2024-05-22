import java.util.*;

class TrieNode {
    Map<Character, TrieNode> children;
    boolean isEndOfWord;

    public TrieNode() {
        this.children = new HashMap<>();
        this.isEndOfWord = false;
    }
}

class Trie {
    private TrieNode root;

    public Trie() {
        this.root = new TrieNode();
    }

    public void insert(String word) {
        TrieNode current = root;
        for (int i = 0; i < word.length(); i++) {
            char ch = word.charAt(i);
            TrieNode node = current.children.get(ch);
            if (node == null) {
                node = new TrieNode();
                current.children.put(ch, node);
            }
            current = node;
        }
        current.isEndOfWord = true;
    }

    public List<String> searchPrefix(String prefix) {
        List<String> results = new ArrayList<>();
        TrieNode current = root;
        for (int i = 0; i < prefix.length(); i++) {
            char ch = prefix.charAt(i);
            TrieNode node = current.children.get(ch);
            if (node == null) {
                return results; // No words with this prefix
            }
            current = node;
        }
        findAllWords(current, prefix, results);
        return results;
    }

    private void findAllWords(TrieNode node, String prefix, List<String> results) {
        if (node.isEndOfWord) {
            results.add(prefix);
        }
        for (char ch : node.children.keySet()) {
            findAllWords(node.children.get(ch), prefix + ch, results);
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Trie trie = new Trie();
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        String[] words = input.split(",");
        for (String word : words){
            trie.insert(word);
        }
        String searchInput = scanner.next();
        List<String> results = trie.searchPrefix(searchInput);
        for (int i = 0 ; i < results.size() ; i++){
            System.out.print(results.get(i));
            if (i < results.size() - 1){
                System.out.print(",");
            }
        }
    }
}


/*  Reza Asadi (Github : RezaGooner)
	1403/03/02 ~ 2024/05/22
*/
