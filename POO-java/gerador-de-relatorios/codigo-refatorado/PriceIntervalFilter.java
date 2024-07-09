import java.util.List;

public class PriceIntervalFilter implements Filter{

    @Override 
    public boolean select(Produto product, List<String> parameter1){
        return (product.getPreco() >= Double.parseDouble(parameter1.get(0))) && (product.getPreco() <= Double.parseDouble(parameter1.get(1)));
    }
}