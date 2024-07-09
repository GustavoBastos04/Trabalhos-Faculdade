import java.util.List;

public class CategoryEqualsThanFilter implements Filter {

    @Override
    public boolean select(Produto product, List<String> parameter){
        return product.getCategoria().equalsIgnoreCase(parameter.get(0));
    }
}