import java.io.PrintWriter;

public class ItalicFormatted extends FormattedDecorator{
    
    public String color;

    public ItalicFormatted(Formatted formatted,String color){
        super(formatted);
        this.color = color;
    }
    @Override
    public void formatting(PrintWriter out, Produto product){
        out.print("<span style =\"font-style:italic; color:"+color+";\">");
        super.formatting(out, product);
        out.print("</span>");
    }
}