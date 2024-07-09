
import java.io.PrintWriter;

public class DefaultFormatted implements Formatted {

    @Override
    public void formatting(PrintWriter out, Produto product){
        out.print(product.formataParaImpressao());
    }
}