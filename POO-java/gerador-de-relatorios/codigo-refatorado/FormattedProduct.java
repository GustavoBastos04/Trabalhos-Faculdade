
import java.text.NumberFormat;

public class FormattedProduct implements Produto {

    private static final String SEPARADOR = ", ";

    private int id;
    private String descricao;
    private String categoria;
    private int qtdEstoque;
    private double preco;
    private boolean bold;
    private boolean italic;
    private String color;
    public FormattedProduct(int id, String descricao, String categoria, int qtdEstoque, double preco, boolean bold, boolean italic, String color) {

        setId(id);
        setDescricao(descricao);
        setCategoria(categoria);
        setQtdEstoque(qtdEstoque);
        setPreco(preco);
        setBold(bold);
        setItalic(italic);
        setColor(color);
    }

    // setters	
    private void setId(int id) {

        this.id = id;
    }

    private void setDescricao(String descricao) {

        this.descricao = descricao;
    }

    private void setCategoria(String categoria) {

        this.categoria = categoria;
    }
    
    public void setQtdEstoque(int qtdEstoque) {

        this.qtdEstoque = qtdEstoque;
    }
    
    public void setPreco(double preco) {

        this.preco = preco;
    }

    public void setBold(boolean bold){

        this.bold = bold;
    }

    public void setItalic(boolean italic){
        this.italic = italic;
    }

    public void setColor(String color){
        this.color = color;
    }
    // getters
    
    public int getId() {

        return this.id;
    }
    
    public String getDescricao() {

        return this.descricao;
    }
    
    public String getCategoria() {

        return this.categoria;
    }
    
    public int getQtdEstoque() {

        return this.qtdEstoque;
    }
    
    public double getPreco() {

        return this.preco;
    }

    public boolean getBold(){
        return this.bold;
    }

    public boolean getItalic(){
        return this.italic;
    }

    public String getColor(){
        return this.color;
    }
    // metodo que devolve uma String que representa o produto, a ser usada na geração dos relatorios.
    public String formataParaImpressao() {

        NumberFormat fmt = NumberFormat.getCurrencyInstance();

        return getDescricao() + SEPARADOR + getCategoria() + SEPARADOR + fmt.format(getPreco()) + SEPARADOR + getQtdEstoque() + " unidade(s) em estoque";
    }

}
