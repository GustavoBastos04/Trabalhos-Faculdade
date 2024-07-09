import java.io.PrintWriter;

public class ItalicAndBoldFormatted extends FormattedDecorator{

    public String color;

    public ItalicAndBoldFormatted(Formatted formatted, String color) {
        super(formatted);
        this.color = color;
    }
    @Override
    public void formatting(PrintWriter out, Produto product){
        out.print("<span style =\"font-weight:bold; font-style:italic; color:"+color+";\">");
        super.formatting(out, product);
        out.print("</span>");
    }

}