import java.util.List;

public class LessStockThanFilter implements Filter{

    @Override
    public boolean select(Produto product, List<String> parameter){
        
        return !(product.getQtdEstoque() > Integer.parseInt(parameter.get(0)));
    }
}