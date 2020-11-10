let mapleader =","

if ! filereadable(system('echo -n "${XDG_CONFIG_HOME:-$HOME/.config}/nvim/autoload/plug.vim"'))
	echo "Downloading junegunn/vim-plug to manage plugins..."
	silent !mkdir -p ${XDG_CONFIG_HOME:-$HOME/.config}/nvim/autoload/
	silent !curl "https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim" > ${XDG_CONFIG_HOME:-$HOME/.config}/nvim/autoload/plug.vim
	autocmd VimEnter * PlugInstall
endif

call plug#begin(system('echo -n "${XDG_CONFIG_HOME:-$HOME/.config}/nvim/plugged"'))

Plug 'itchyny/lightline.vim'                      " Vim Lightline
Plug 'chrisbra/Colorizer'                         " color from rgb
Plug 'vimwiki/vimwiki'                            " vimwiki
Plug 'mcchrish/nnn.vim'                           " nnn file picker
Plug 'AndrewRadev/id3.vim'                        " id3tag editor
Plug 'junegunn/fzf.vim'                           " vim fzf
" Plug 'vim-airline/vim-airline'				  " Airline
" Plug 'vim-airline/vim-airline-themes'			  " Airline Themes
" Plug 'flazz/vim-colorschemes'                   " vim colorscheme
" Plug 'chrisbra/unicode.vim'                     " unicode search

call plug#end()

"execute pathogen#infect()
filetype plugin indent on    " required

set nocompatible              " be iMproved, required
filetype off                  " required

"Remap ESC to jj 
:imap jj <Esc>

"Disable arrow keys in Normal mode
no <Up> <Nop>
no <Down> <Nop>
no <Left> <Nop>
no <Right> <Nop>

"Disable arrow keys in Insert mode
ino <Up> <Nop>
ino <Down> <Nop>
ino <Left> <Nop>
ino <Right> <Nop>

" Shortcutting split navigation, saving a keypress:
map <C-h> <C-w>h
map <C-j> <C-w>j
map <C-k> <C-w>k
map <C-l> <C-w>l

map <leader>sp :sp
map <leader>sv :vsp

" tab management
map <leader>te :tabe
map <leader>tn :tabnew<cr>
map <leader>tx :tabnext
map <leader>tm :tabmove
map <leader>tc :tabclose<cr>
map <leader>to :tabonly<cr>

"Copy paste Clipboard Access:
vnoremap <C-c> "+y
map <C-p> "+P

" Spell-check set to <leader>o, 'o' for 'orthography':
map <leader>s :setlocal spell! spelllang=en_us<CR>

" Compile document, be it groff/LaTeX/markdown/etc.
map <leader>c :w! \| !compiler <c-r>%<CR>

" Open corresponding .pdf/.html or preview
map <leader>p :!opout <c-r>%<CR><CR>

map <leader>h :ColorHighlight
noremap <leader>u :w \| startinsert \| term urlview %<cr>

":nnoremap <leader>u :silent w\|!urlview %<CR>

" Enable autocompletion:
set wildmode=longest,list,full
" Disables automatic commenting on newline:
autocmd FileType * setlocal formatoptions-=c formatoptions-=r formatoptions-=o

syntax on

set laststatus=2
set t_Co=256
set encoding=utf-8
set relativenumber
set number
set showcmd
set noshowmode
set expandtab
set smarttab
set shiftwidth=4
set tabstop=4
set hlsearch

set path+=**					" Searches current directory recursively.
set wildmenu					" Display all matches when tab complete.
set incsearch
set nobackup
set noswapfile
set splitbelow splitright

hi LineNr ctermfg=242
hi CursorLineNr ctermfg=15
hi VertSplit ctermfg=8 ctermbg=0
hi Statement ctermfg=3


let g:python_highlight_all = 1

let g:rehash256 = 1
let g:lightline = {
      \ 'colorscheme': 'OldHope',
      \ }

" fzf
set rtp+=/usr/bin/fzf
nnoremap <silent> <leader>f :AF<CR>

if exists('$TMUX')
  let g:fzf_layout = { 'tmux': '-p90%,60%' }
else
  let g:fzf_layout = { 'window': { 'width': 0.9, 'height': 0.6 } }
endif


let g:fzf_action = {
  \ 'ctrl-t': 'tab split',
  \ 'ctrl-x': 'split',
  \ 'ctrl-v': 'vsplit' }

command! -nargs=? -complete=dir AF
 \ call fzf#run(fzf#wrap(fzf#vim#with_preview({
  \   'source': 'find ~/ -type f 2> /dev/null '.expand(<q-args>)
  \ })))

":vimwiki ext
let g:vimwiki_list = [{'path': '~/vimwiki/',
                       \ 'syntax': 'markdown', 'ext': '.md'}]

" nnn
let g:nnn#set_default_mappings = 0
nnoremap <silent> <leader>nnn :NnnPicker<CR>
" let g:nnn#action = {
"             \ '<c-t>': 'tab split',
"             \ '<c-x>': 'split',
"             \ '<c-v>': 'vsplit'
"             \ }
