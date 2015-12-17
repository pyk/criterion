/* indent(1) Profile
 * This is list of options that will be used by indent(1) to formatting the 
 * C source code.
 * 
 * For complete available options 
 * https://www.gnu.org/software/indent/manual/html_section/indent_15.html#SEC17
 *
 * Copyright 2015 Bayu Aldi Yansyah <bayualdiyansyah@gmail.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Maximum line length is 78 */
--line-length78

/* Indentation level 4 spaces */
--indent-level4
--declaration-indentation0

/* Blank lines */
--no-blank-lines-after-declarations
--blank-lines-after-procedures
--continue-at-parentheses
--swallow-optional-blank-lines

/* Function */
--dont-break-function-decl-args
--no-parameter-indentation
--no-space-after-function-call-names

/* Comment */
--dont-format-comments
--dont-format-first-column-comments

/* Brace */
--braces-after-func-def-line
--braces-on-if-line
--braces-on-struct-decl-line

/* switch statement */
--case-indentation0

/* while statement */
--cuddle-do-while
--no-space-after-while

/* for statement */
--no-space-after-for

/* if statement */
--cuddle-else
--no-space-after-if

/* Other */
--no-space-after-parentheses
--no-tabs
--space-special-semicolon
--preserve-mtime
--no-space-after-casts