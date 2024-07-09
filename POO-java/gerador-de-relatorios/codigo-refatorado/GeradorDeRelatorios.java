import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Scanner;

public class GeradorDeRelatorios {

	private List<Produto> produtos;
	private Sort algoritmo;
	private Criteria criterio;
	private Filter filtro;
	private List<String> argFiltro;
	private Boolean italic;
	private Boolean bold;	
	private Boolean color;

	public GeradorDeRelatorios(List<Produto> produtos, Sort algoritmo, Criteria criterio, Filter filtro, List<String> argFiltro, Boolean bold, Boolean italic, Boolean color){

		this.produtos = produtos;
		this.algoritmo = algoritmo;
		this.criterio = criterio;
		this.filtro = filtro;
		this.argFiltro = argFiltro;
		this.italic = italic;
		this.bold = bold;
		this.color = color;
	}
	
	public void debug(){

		System.out.println("Gerando relatório para array contendo " + produtos.size() + " produto(s)");
		System.out.println("parametro filtro = '" + argFiltro + "'"); 
	}


	public void geraRelatorio(String arquivoSaida) throws IOException {

		debug();

		algoritmo.ordena(produtos, criterio, 0, produtos.size()-1);

		PrintWriter out = new PrintWriter(arquivoSaida);

		out.println("<!DOCTYPE html><html>");
		out.println("<head><title>Relatorio de produtos</title>");
		out.println("<meta charset=\"UTF-8\">");
		out.println("</head>");
		out.println("<body>");
		out.println("Relatorio de Produtos:");
		out.println("<ul>");

		int count = 0;

		for(int i = 0; i < produtos.size(); i++){

			Produto p = produtos.get(i);
			FormattedProduct p2 = (FormattedProduct) p;

			if(filtro.select(p, argFiltro) == true){

				out.print("<li>");
				
				Formatted noneFormatted = new DefaultFormatted();
				Formatted  printFormatted;
				if(italic && bold && color){
					printFormatted = new ItalicAndBoldFormatted(noneFormatted, p2.getColor());
				}
				else if(bold && color){
					printFormatted = new BoldFormatted(noneFormatted, p2.getColor());
				}
				else if (italic && color){
					printFormatted = new ItalicFormatted(noneFormatted, p2.getColor());
				}
				else if(bold && italic){
					printFormatted = new ItalicAndBoldFormatted(noneFormatted, "#000000");
				}
				else if(bold){
					printFormatted = new BoldFormatted(noneFormatted, "#000000");
				}
				else if(italic){
					printFormatted = new ItalicFormatted(noneFormatted, "#000000");
				}
				else {
					// Como em "produtos.csv" os produtos possuem ao menos a cor preta, podemos cosiderar coloridas
					printFormatted = new ColoredFormatted(noneFormatted, "#000000");
				}
				printFormatted.formatting(out, p);
				
				out.println("</li>");
				count++;
			}
		}

		out.println("</ul>");
		out.println(count + " produtos listados, de um total de " + produtos.size() + ".");
		out.println("</body>");
		out.println("</html>");

		out.close();
	}

	public static List<Produto> carregaProdutos(String productsFile){
		List<Produto> loadedProducts = new ArrayList<>();
		Scanner scan = null;
		try{
			
			scan = new Scanner ((new File(productsFile)));
			scan.nextLine();
		    scan.useDelimiter(", |\n");
			scan.useLocale(Locale.US);
			while(scan.hasNext()){
				int id = scan.nextInt();
                String descricao = scan.next();
                String categoria = scan.next();
                int qtdEstoque = scan.nextInt();
                double preco = scan.nextDouble();
                boolean negrito = scan.nextBoolean();
                boolean italico = scan.nextBoolean();
                String cor = scan.next();
                            
				loadedProducts.add( 
					new FormattedProduct(id, descricao, categoria, qtdEstoque, preco, negrito, italico, cor));
			}
		}
		catch (FileNotFoundException e){
			System.err.println("Não foi possível ler o arquivo: " + e);
		}
		finally{
			if(scan != null) scan.close();
		}

		return loadedProducts;
	} 

	public static void main(String [] args) {

		if(args.length < 4){

			System.out.println("Uso:");
			System.out.println("\tjava " + GeradorDeRelatorios.class.getName() + " <algoritmo> <critério de ordenação> <critério de filtragem> <parâmetro de filtragem> <opções de formatação>");
			System.out.println("Onde:");
			System.out.println("\talgoritmo: 'quick' ou 'insertion'");
			System.out.println("\tcriterio de ordenação: 'preco_c' ou 'descricao_c' ou 'estoque_c' ou preco_dc ou descricao_dc ou estoque_dc");
			System.out.println("\tcriterio de filtragem: 'todos' ou 'estoque_menor_igual' ou 'categoria_igual' ou 'substring' ou 'intervalo_de_preco'"); 
			System.out.println("\tparâmetro de filtragem: argumentos adicionais necessários para a filtragem -`escreva o intervalo do menor para o maior no caso de intervalo_de_preco"); 
			System.out.println("\topções de formatação: 'negrito' e/ou 'italico' e/ou 'cor'");
			System.out.println();
			System.exit(1);
		}

		String str_algoritmo = args[0];
		Sort opcao_algoritmo = null;

		if( str_algoritmo.equals("insertion")){
			
			opcao_algoritmo = new InsertionSort();
		}
		else if( str_algoritmo.equals("quick")){
			
			opcao_algoritmo = new QuickSort();
		}
		
		String str_criterio_ord = args[1];
		Criteria opcao_criterio_ord = null;

		switch (str_criterio_ord){

			case "preco_c":
				opcao_criterio_ord = new AscendingPriceCriteria();
				break;

			case "descricao_c":
				opcao_criterio_ord = new AscendingDescCriteria();
				break;

			case "estoque_c":
				opcao_criterio_ord = new AscendingStockCriteria();
				break;
			
			case "preco_dc":
				opcao_criterio_ord = new DescendingPriceCriteria();
				break;

			case "descricao_dc":
				opcao_criterio_ord = new DescendingDescCriteria();
				break;
			case "estoque_dc":
				opcao_criterio_ord = new DescendingStockCriteria();
				break;

			default:
				break;
		}

		String str_criterio_filtro = args[2];
		Filter opcao_criterio_filtro = null;

		switch (str_criterio_filtro) {
			
			case "todos":
				
				opcao_criterio_filtro = new AllProductsFilter();
				break;
			case "estoque_menor_igual":
				
				opcao_criterio_filtro = new LessStockThanFilter();
				break;
			
			case "categoria_igual":
				
				opcao_criterio_filtro = new CategoryEqualsThanFilter();
				break;

			case "substring":
				opcao_criterio_filtro = new SubstringFilter();
				break;

			case "intervalo_de_preco":
				opcao_criterio_filtro = new PriceIntervalFilter();
				break;
			default: 
				break;

		}

		List<String> opcao_parametro_filtro = new ArrayList<>();
		
		boolean opcao_negrito = false;
        boolean opcao_italico = false;
		boolean opcao_color = false;
		
		opcao_parametro_filtro.add(args[3]);

		if(opcao_criterio_filtro instanceof PriceIntervalFilter){
			
			opcao_parametro_filtro.add(args[4]);
		}
        for (String arg : args) {
            if (arg.equalsIgnoreCase("negrito")) {
                opcao_negrito = true;
            }
            if (arg.equalsIgnoreCase("italico")) {
                opcao_italico = true;
            }
            if (arg.equalsIgnoreCase("cor")) {
                opcao_color = true;
            }
        }

		GeradorDeRelatorios gdr = new GeradorDeRelatorios(	carregaProdutos("../produtos.csv"), 
									opcao_algoritmo,
									opcao_criterio_ord,
									opcao_criterio_filtro,
									opcao_parametro_filtro,
									opcao_negrito,
									opcao_italico,
									opcao_color
								 );

		try{
			gdr.geraRelatorio("saida.html");
		}
		catch(IOException e){
			
			e.printStackTrace();
		}
	}
}
