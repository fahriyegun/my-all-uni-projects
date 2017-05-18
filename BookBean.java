package entity;

/**
 * Created by Fahriye on 10.8.2016.
 */

//bean class
import dao.Dao;
import java.util.ArrayList;
import java.util.List;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;

@ManagedBean (name = "BookBean")
@SessionScoped

public class BookBean implements java.io.Serializable{
   public int book_id;
   public String book_name,  author, genre;
   public int page, price;
   public String msg;
   public int selectedname;

    public BookBean() {}

    public int getBook_id() {
        return book_id;
    }

    public void setBook_id(int book_id) {
        this.book_id = book_id;
    }

    public String getBook_name() {
        return book_name;
    }

    public void setBook_name(String book_name) {
        this.book_name = book_name;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public String getGenre() {
        return genre;
    }

    public void setGenre(String genre) {
        this.genre = genre;
    }

    public int getPage() {
        return page;
    }

    public void setPage(int page) {
        this.page = page;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public int getSelectedname() {
        return selectedname;
    }

    public void setSelectedname(int selectedname) {
        this.selectedname = selectedname;
    }

    public void saveBook() {
        Dao dao = new Dao();
        Book book=new Book();
        book.setBook_name(this.book_name);
        book.setAuthor(this.author);
        book.setGenre(this.genre);
        book.setPage(this.page);
        book.setPrice(this.price);
        dao.addBook(book);
        this.msg = "Book Info Saved Successfull!";
        clearAll();
    }
    public void updateBook() {
        Dao dao = new Dao();
        Book book=new Book();
        book.setBook_id(this.book_id);
        book.setBook_name(this.book_name);
        book.setAuthor(this.author);
        book.setGenre(this.genre);
        book.setPage(this.page);
        book.setPrice(this.price);
        dao.updateBook(book);
        this.msg = "Book Info Update Successfull!";
        //clearAll();
    }
    public void deleteBook() {
        Dao dao = new Dao();
        Book book=new Book();
        book.setBook_id(this.book_id);
        book.setBook_name(this.book_name);
        book.setAuthor(this.author);
        book.setGenre(this.genre);
        book.setPage(this.page);
        book.setPrice(this.price);
        dao.deleteBook(book.book_id);
        this.msg = "Book Info Delete Successfull!";
        //clearAll();
    }

    public List<Book> getAllBooks() {
        List<Book> users = new ArrayList<Book>();
        Dao dao = new Dao();
        users = dao.getAllBooks();
        return users;
    }

    public void fullInfo() {
        Dao dao = new Dao();
        List<Book> lc = dao.getBookById(selectedname);
        System.out.println(lc.get(0).author);
        this.book_id = lc.get(0).book_id;
        this.book_name = lc.get(0).book_name;
        this.author = lc.get(0).author;
        this.genre = lc.get(0).genre;
        this.page = lc.get(0).page;
        this.price = lc.get(0).price;
    }

   public void clearAll() {
        this.author = "";
        this.genre = "";
        this.page = 0;
        this.price = 0;
        this.book_name="";
    }
}

