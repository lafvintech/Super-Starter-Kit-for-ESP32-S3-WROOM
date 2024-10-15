# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

#import sphinx_conestack_theme
from pygments.lexers import Python3Lexer
import time

project = 'Basic Starter Kit'
copyright = '2024, LAFVIN'
author = 'LAFVIN'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ["myst_parser"]
pygments_lexers = {
    "python-repl": Python3Lexer(),
}

source_suffix = {
    '.rst': 'restructuredtext',
    '.md': 'markdown',
}

templates_path = ['_templates']
exclude_patterns = []



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

#html_theme = 'conestack'
#html_theme_path = [sphinx_pdj_theme.get_html_theme_path()]
html_theme = 'sphinx_rtd_theme'
#html_theme = 'press'

# html_static_path = ['_static']
# html_logo = '_static/Logo2.png'

html_theme_options = {
     'logo_only': True,
     'display_version': False,
 }