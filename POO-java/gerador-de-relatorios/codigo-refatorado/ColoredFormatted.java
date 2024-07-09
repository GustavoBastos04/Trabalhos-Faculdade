import java.io.PrintWriter;

public class ColoredFormatted extends  FormattedDecorator{

    public String color;

    public ColoredFormatted(Formatted formatted, String color){
        super(formatted);
        this.color = color;
    }

    @Override
    public void formatting(PrintWriter out, Produto product){
        out.print("<span style=\"color:"+color+"\">");
        super.formatting(out, product);
        out.print("</span>");
    }
}