import java.io.PrintWriter;

public class FormattedDecorator implements Formatted{
    public Formatted formatted;

    public FormattedDecorator(Formatted formatted){
        this.formatted = formatted;
    }

    @Override
    public void formatting(PrintWriter out, Produto product){
        formatted.formatting(out, product);
    }
}