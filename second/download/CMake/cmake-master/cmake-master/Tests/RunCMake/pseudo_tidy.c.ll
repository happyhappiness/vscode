; ModuleID = '/data/download/cmake/cmake-master/Tests/RunCMake/pseudo_tidy.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@.str = private unnamed_addr constant [5 x i8] c"-bad\00", align 1
@stdout = external global %struct._IO_FILE*, align 8
@.str.1 = private unnamed_addr constant [41 x i8] c"stdout from bad command line arg '-bad'\0A\00", align 1
@stderr = external global %struct._IO_FILE*, align 8
@.str.2 = private unnamed_addr constant [41 x i8] c"stderr from bad command line arg '-bad'\0A\00", align 1
@.str.3 = private unnamed_addr constant [36 x i8] c"%s:0:0: warning: message [checker]\0A\00", align 1
@.str.4 = private unnamed_addr constant [22 x i8] c"1 warning generated.\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main(i32 %argc, i8** %argv) #0 !dbg !4 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %i = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %argc.addr, metadata !14, metadata !15), !dbg !16
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %argv.addr, metadata !17, metadata !15), !dbg !18
  call void @llvm.dbg.declare(metadata i32* %i, metadata !19, metadata !15), !dbg !20
  store i32 1, i32* %i, align 4, !dbg !21
  br label %for.cond, !dbg !23

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !24
  %1 = load i32, i32* %argc.addr, align 4, !dbg !27
  %cmp = icmp slt i32 %0, %1, !dbg !28
  br i1 %cmp, label %for.body, label %for.end, !dbg !29

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %i, align 4, !dbg !30
  %idxprom = sext i32 %2 to i64, !dbg !33
  %3 = load i8**, i8*** %argv.addr, align 8, !dbg !33
  %arrayidx = getelementptr inbounds i8*, i8** %3, i64 %idxprom, !dbg !33
  %4 = load i8*, i8** %arrayidx, align 8, !dbg !33
  %call = call i32 @strcmp(i8* %4, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0)) #4, !dbg !34
  %cmp1 = icmp eq i32 %call, 0, !dbg !35
  br i1 %cmp1, label %if.then, label %if.end, !dbg !36

if.then:                                          ; preds = %for.body
  %5 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !37
  %call2 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %5, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.1, i32 0, i32 0)), !dbg !39
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !40
  %call3 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %6, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.2, i32 0, i32 0)), !dbg !41
  store i32 1, i32* %retval, align 4, !dbg !42
  br label %return, !dbg !42

if.end:                                           ; preds = %for.body
  %7 = load i32, i32* %i, align 4, !dbg !43
  %idxprom4 = sext i32 %7 to i64, !dbg !45
  %8 = load i8**, i8*** %argv.addr, align 8, !dbg !45
  %arrayidx5 = getelementptr inbounds i8*, i8** %8, i64 %idxprom4, !dbg !45
  %9 = load i8*, i8** %arrayidx5, align 8, !dbg !45
  %arrayidx6 = getelementptr inbounds i8, i8* %9, i64 0, !dbg !45
  %10 = load i8, i8* %arrayidx6, align 1, !dbg !45
  %conv = sext i8 %10 to i32, !dbg !45
  %cmp7 = icmp ne i32 %conv, 45, !dbg !46
  br i1 %cmp7, label %if.then9, label %if.end13, !dbg !47

if.then9:                                         ; preds = %if.end
  %11 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !48
  %12 = load i32, i32* %i, align 4, !dbg !50
  %idxprom10 = sext i32 %12 to i64, !dbg !51
  %13 = load i8**, i8*** %argv.addr, align 8, !dbg !51
  %arrayidx11 = getelementptr inbounds i8*, i8** %13, i64 %idxprom10, !dbg !51
  %14 = load i8*, i8** %arrayidx11, align 8, !dbg !51
  %call12 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %11, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.3, i32 0, i32 0), i8* %14), !dbg !52
  br label %for.end, !dbg !53

if.end13:                                         ; preds = %if.end
  br label %for.inc, !dbg !54

for.inc:                                          ; preds = %if.end13
  %15 = load i32, i32* %i, align 4, !dbg !55
  %inc = add nsw i32 %15, 1, !dbg !55
  store i32 %inc, i32* %i, align 4, !dbg !55
  br label %for.cond, !dbg !57

for.end:                                          ; preds = %if.then9, %for.cond
  %16 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !58
  %call14 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %16, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.4, i32 0, i32 0)), !dbg !59
  store i32 0, i32* %retval, align 4, !dbg !60
  br label %return, !dbg !60

return:                                           ; preds = %for.end, %if.then
  %17 = load i32, i32* %retval, align 4, !dbg !61
  ret i32 %17, !dbg !61
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #2

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!11, !12}
!llvm.ident = !{!13}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Tests/RunCMake/pseudo_tidy.c", directory: "/data/download/cmake/cmake-master/Tests/RunCMake")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 4, type: !5, isLocal: false, isDefinition: true, scopeLine: 5, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !7, !8}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!11 = !{i32 2, !"Dwarf Version", i32 4}
!12 = !{i32 2, !"Debug Info Version", i32 3}
!13 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!14 = !DILocalVariable(name: "argc", arg: 1, scope: !4, file: !1, line: 4, type: !7)
!15 = !DIExpression()
!16 = !DILocation(line: 4, column: 14, scope: !4)
!17 = !DILocalVariable(name: "argv", arg: 2, scope: !4, file: !1, line: 4, type: !8)
!18 = !DILocation(line: 4, column: 26, scope: !4)
!19 = !DILocalVariable(name: "i", scope: !4, file: !1, line: 6, type: !7)
!20 = !DILocation(line: 6, column: 7, scope: !4)
!21 = !DILocation(line: 7, column: 10, scope: !22)
!22 = distinct !DILexicalBlock(scope: !4, file: !1, line: 7, column: 3)
!23 = !DILocation(line: 7, column: 8, scope: !22)
!24 = !DILocation(line: 7, column: 15, scope: !25)
!25 = !DILexicalBlockFile(scope: !26, file: !1, discriminator: 1)
!26 = distinct !DILexicalBlock(scope: !22, file: !1, line: 7, column: 3)
!27 = !DILocation(line: 7, column: 19, scope: !25)
!28 = !DILocation(line: 7, column: 17, scope: !25)
!29 = !DILocation(line: 7, column: 3, scope: !25)
!30 = !DILocation(line: 8, column: 21, scope: !31)
!31 = distinct !DILexicalBlock(scope: !32, file: !1, line: 8, column: 9)
!32 = distinct !DILexicalBlock(scope: !26, file: !1, line: 7, column: 30)
!33 = !DILocation(line: 8, column: 16, scope: !31)
!34 = !DILocation(line: 8, column: 9, scope: !31)
!35 = !DILocation(line: 8, column: 33, scope: !31)
!36 = !DILocation(line: 8, column: 9, scope: !32)
!37 = !DILocation(line: 9, column: 15, scope: !38)
!38 = distinct !DILexicalBlock(scope: !31, file: !1, line: 8, column: 39)
!39 = !DILocation(line: 9, column: 7, scope: !38)
!40 = !DILocation(line: 10, column: 15, scope: !38)
!41 = !DILocation(line: 10, column: 7, scope: !38)
!42 = !DILocation(line: 11, column: 7, scope: !38)
!43 = !DILocation(line: 13, column: 14, scope: !44)
!44 = distinct !DILexicalBlock(scope: !32, file: !1, line: 13, column: 9)
!45 = !DILocation(line: 13, column: 9, scope: !44)
!46 = !DILocation(line: 13, column: 20, scope: !44)
!47 = !DILocation(line: 13, column: 9, scope: !32)
!48 = !DILocation(line: 14, column: 15, scope: !49)
!49 = distinct !DILexicalBlock(scope: !44, file: !1, line: 13, column: 28)
!50 = !DILocation(line: 14, column: 68, scope: !49)
!51 = !DILocation(line: 14, column: 63, scope: !49)
!52 = !DILocation(line: 14, column: 7, scope: !49)
!53 = !DILocation(line: 15, column: 7, scope: !49)
!54 = !DILocation(line: 17, column: 3, scope: !32)
!55 = !DILocation(line: 7, column: 25, scope: !56)
!56 = !DILexicalBlockFile(scope: !26, file: !1, discriminator: 2)
!57 = !DILocation(line: 7, column: 3, scope: !56)
!58 = !DILocation(line: 18, column: 11, scope: !4)
!59 = !DILocation(line: 18, column: 3, scope: !4)
!60 = !DILocation(line: 19, column: 3, scope: !4)
!61 = !DILocation(line: 20, column: 1, scope: !4)
