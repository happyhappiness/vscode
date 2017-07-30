; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmexpat/lib/xmlrole.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.prolog_state = type { i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)*, i32, i32 }
%struct.encoding = type { [3 x i32 (%struct.encoding*, i8*, i8*, i8**)*], [2 x i32 (%struct.encoding*, i8*, i8*, i8**)*], i32 (%struct.encoding*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*)*, i8* (%struct.encoding*, i8*)*, i32 (%struct.encoding*, i8*, i32, %struct.ATTRIBUTE*)*, i32 (%struct.encoding*, i8*)*, i32 (%struct.encoding*, i8*, i8*)*, void (%struct.encoding*, i8*, i8*, %struct.position*)*, i32 (%struct.encoding*, i8*, i8*, i8**)*, i32 (%struct.encoding*, i8**, i8*, i8**, i8*)*, i32 (%struct.encoding*, i8**, i8*, i16**, i16*)*, i32, i8, i8 }
%struct.ATTRIBUTE = type { i8*, i8*, i8*, i8 }
%struct.position = type { i64, i64 }

@KW_DOCTYPE = internal constant [8 x i8] c"DOCTYPE\00", align 1
@KW_SYSTEM = internal constant [7 x i8] c"SYSTEM\00", align 1
@KW_PUBLIC = internal constant [7 x i8] c"PUBLIC\00", align 1
@KW_ENTITY = internal constant [7 x i8] c"ENTITY\00", align 1
@KW_ATTLIST = internal constant [8 x i8] c"ATTLIST\00", align 1
@KW_ELEMENT = internal constant [8 x i8] c"ELEMENT\00", align 1
@KW_NOTATION = internal constant [9 x i8] c"NOTATION\00", align 1
@KW_NDATA = internal constant [6 x i8] c"NDATA\00", align 1
@attlist2.types = internal constant [8 x i8*] [i8* getelementptr inbounds ([6 x i8], [6 x i8]* @KW_CDATA, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @KW_ID, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @KW_IDREF, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @KW_IDREFS, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @KW_ENTITY, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @KW_ENTITIES, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @KW_NMTOKEN, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @KW_NMTOKENS, i32 0, i32 0)], align 16
@KW_CDATA = internal constant [6 x i8] c"CDATA\00", align 1
@KW_ID = internal constant [3 x i8] c"ID\00", align 1
@KW_IDREF = internal constant [6 x i8] c"IDREF\00", align 1
@KW_IDREFS = internal constant [7 x i8] c"IDREFS\00", align 1
@KW_ENTITIES = internal constant [9 x i8] c"ENTITIES\00", align 1
@KW_NMTOKEN = internal constant [8 x i8] c"NMTOKEN\00", align 1
@KW_NMTOKENS = internal constant [9 x i8] c"NMTOKENS\00", align 1
@KW_IMPLIED = internal constant [8 x i8] c"IMPLIED\00", align 1
@KW_REQUIRED = internal constant [9 x i8] c"REQUIRED\00", align 1
@KW_FIXED = internal constant [6 x i8] c"FIXED\00", align 1
@KW_EMPTY = internal constant [6 x i8] c"EMPTY\00", align 1
@KW_ANY = internal constant [4 x i8] c"ANY\00", align 1
@KW_PCDATA = internal constant [7 x i8] c"PCDATA\00", align 1

; Function Attrs: nounwind uwtable
define void @XmlPrologStateInit(%struct.prolog_state* %state) #0 !dbg !74 {
entry:
  %state.addr = alloca %struct.prolog_state*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !268, metadata !269), !dbg !270
  %0 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !271
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %0, i32 0, i32 0, !dbg !272
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @prolog0, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !273
  ret void, !dbg !274
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i32 @prolog0(%struct.prolog_state* %state, i32 %tok, i8* %ptr, i8* %end, %struct.encoding* %enc) #0 !dbg !173 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %end.addr = alloca i8*, align 8
  %enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !275, metadata !269), !dbg !276
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !277, metadata !269), !dbg !278
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !279, metadata !269), !dbg !280
  store i8* %end, i8** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %end.addr, metadata !281, metadata !269), !dbg !282
  store %struct.encoding* %enc, %struct.encoding** %enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %enc.addr, metadata !283, metadata !269), !dbg !284
  %0 = load i32, i32* %tok.addr, align 4, !dbg !285
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 12, label %sw.bb1
    i32 11, label %sw.bb3
    i32 13, label %sw.bb5
    i32 14, label %sw.bb7
    i32 16, label %sw.bb8
    i32 29, label %sw.bb10
  ], !dbg !286

sw.bb:                                            ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !287
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !289
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @prolog1, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !290
  store i32 0, i32* %retval, align 4, !dbg !291
  br label %return, !dbg !291

sw.bb1:                                           ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !292
  %handler2 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %2, i32 0, i32 0, !dbg !293
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @prolog1, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler2, align 8, !dbg !294
  store i32 1, i32* %retval, align 4, !dbg !295
  br label %return, !dbg !295

sw.bb3:                                           ; preds = %entry
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !296
  %handler4 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %3, i32 0, i32 0, !dbg !297
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @prolog1, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler4, align 8, !dbg !298
  store i32 55, i32* %retval, align 4, !dbg !299
  br label %return, !dbg !299

sw.bb5:                                           ; preds = %entry
  %4 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !300
  %handler6 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %4, i32 0, i32 0, !dbg !301
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @prolog1, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler6, align 8, !dbg !302
  store i32 56, i32* %retval, align 4, !dbg !303
  br label %return, !dbg !303

sw.bb7:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !304
  br label %return, !dbg !304

sw.bb8:                                           ; preds = %entry
  %5 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !305
  %nameMatchesAscii = getelementptr inbounds %struct.encoding, %struct.encoding* %5, i32 0, i32 3, !dbg !305
  %6 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii, align 8, !dbg !305
  %7 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !305
  %8 = load i8*, i8** %ptr.addr, align 8, !dbg !305
  %9 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !305
  %minBytesPerChar = getelementptr inbounds %struct.encoding, %struct.encoding* %9, i32 0, i32 13, !dbg !305
  %10 = load i32, i32* %minBytesPerChar, align 8, !dbg !305
  %mul = mul nsw i32 2, %10, !dbg !305
  %idx.ext = sext i32 %mul to i64, !dbg !305
  %add.ptr = getelementptr inbounds i8, i8* %8, i64 %idx.ext, !dbg !305
  %11 = load i8*, i8** %end.addr, align 8, !dbg !305
  %call = call i32 %6(%struct.encoding* %7, i8* %add.ptr, i8* %11, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @KW_DOCTYPE, i32 0, i32 0)), !dbg !305
  %tobool = icmp ne i32 %call, 0, !dbg !305
  br i1 %tobool, label %if.end, label %if.then, !dbg !307

if.then:                                          ; preds = %sw.bb8
  br label %sw.epilog, !dbg !308

if.end:                                           ; preds = %sw.bb8
  %12 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !309
  %handler9 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %12, i32 0, i32 0, !dbg !310
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @doctype0, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler9, align 8, !dbg !311
  store i32 3, i32* %retval, align 4, !dbg !312
  br label %return, !dbg !312

sw.bb10:                                          ; preds = %entry
  %13 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !313
  %handler11 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %13, i32 0, i32 0, !dbg !314
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @error, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler11, align 8, !dbg !315
  store i32 2, i32* %retval, align 4, !dbg !316
  br label %return, !dbg !316

sw.epilog:                                        ; preds = %entry, %if.then
  %14 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !317
  %15 = load i32, i32* %tok.addr, align 4, !dbg !318
  %call12 = call i32 @common(%struct.prolog_state* %14, i32 %15), !dbg !319
  store i32 %call12, i32* %retval, align 4, !dbg !320
  br label %return, !dbg !320

return:                                           ; preds = %sw.epilog, %sw.bb10, %if.end, %sw.bb7, %sw.bb5, %sw.bb3, %sw.bb1, %sw.bb
  %16 = load i32, i32* %retval, align 4, !dbg !321
  ret i32 %16, !dbg !321
}

; Function Attrs: nounwind uwtable
define internal i32 @prolog1(%struct.prolog_state* %state, i32 %tok, i8* %ptr, i8* %end, %struct.encoding* %enc) #0 !dbg !176 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %end.addr = alloca i8*, align 8
  %enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !322, metadata !269), !dbg !323
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !324, metadata !269), !dbg !325
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !326, metadata !269), !dbg !327
  store i8* %end, i8** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %end.addr, metadata !328, metadata !269), !dbg !329
  store %struct.encoding* %enc, %struct.encoding** %enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %enc.addr, metadata !330, metadata !269), !dbg !331
  %0 = load i32, i32* %tok.addr, align 4, !dbg !332
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 11, label %sw.bb1
    i32 13, label %sw.bb2
    i32 14, label %sw.bb3
    i32 16, label %sw.bb4
    i32 29, label %sw.bb5
  ], !dbg !333

sw.bb:                                            ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !334
  br label %return, !dbg !334

sw.bb1:                                           ; preds = %entry
  store i32 55, i32* %retval, align 4, !dbg !336
  br label %return, !dbg !336

sw.bb2:                                           ; preds = %entry
  store i32 56, i32* %retval, align 4, !dbg !337
  br label %return, !dbg !337

sw.bb3:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !338
  br label %return, !dbg !338

sw.bb4:                                           ; preds = %entry
  %1 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !339
  %nameMatchesAscii = getelementptr inbounds %struct.encoding, %struct.encoding* %1, i32 0, i32 3, !dbg !339
  %2 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii, align 8, !dbg !339
  %3 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !339
  %4 = load i8*, i8** %ptr.addr, align 8, !dbg !339
  %5 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !339
  %minBytesPerChar = getelementptr inbounds %struct.encoding, %struct.encoding* %5, i32 0, i32 13, !dbg !339
  %6 = load i32, i32* %minBytesPerChar, align 8, !dbg !339
  %mul = mul nsw i32 2, %6, !dbg !339
  %idx.ext = sext i32 %mul to i64, !dbg !339
  %add.ptr = getelementptr inbounds i8, i8* %4, i64 %idx.ext, !dbg !339
  %7 = load i8*, i8** %end.addr, align 8, !dbg !339
  %call = call i32 %2(%struct.encoding* %3, i8* %add.ptr, i8* %7, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @KW_DOCTYPE, i32 0, i32 0)), !dbg !339
  %tobool = icmp ne i32 %call, 0, !dbg !339
  br i1 %tobool, label %if.end, label %if.then, !dbg !341

if.then:                                          ; preds = %sw.bb4
  br label %sw.epilog, !dbg !342

if.end:                                           ; preds = %sw.bb4
  %8 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !343
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %8, i32 0, i32 0, !dbg !344
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @doctype0, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !345
  store i32 3, i32* %retval, align 4, !dbg !346
  br label %return, !dbg !346

sw.bb5:                                           ; preds = %entry
  %9 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !347
  %handler6 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %9, i32 0, i32 0, !dbg !348
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @error, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler6, align 8, !dbg !349
  store i32 2, i32* %retval, align 4, !dbg !350
  br label %return, !dbg !350

sw.epilog:                                        ; preds = %entry, %if.then
  %10 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !351
  %11 = load i32, i32* %tok.addr, align 4, !dbg !352
  %call7 = call i32 @common(%struct.prolog_state* %10, i32 %11), !dbg !353
  store i32 %call7, i32* %retval, align 4, !dbg !354
  br label %return, !dbg !354

return:                                           ; preds = %sw.epilog, %sw.bb5, %if.end, %sw.bb3, %sw.bb2, %sw.bb1, %sw.bb
  %12 = load i32, i32* %retval, align 4, !dbg !355
  ret i32 %12, !dbg !355
}

; Function Attrs: nounwind uwtable
define internal i32 @doctype0(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !177 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !356, metadata !269), !dbg !357
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !358, metadata !269), !dbg !359
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !360, metadata !269), !dbg !361
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !362, metadata !269), !dbg !363
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !364, metadata !269), !dbg !365
  %0 = load i32, i32* %tok.addr, align 4, !dbg !366
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 18, label %sw.bb1
    i32 41, label %sw.bb1
  ], !dbg !367

sw.bb:                                            ; preds = %entry
  store i32 3, i32* %retval, align 4, !dbg !368
  br label %return, !dbg !368

sw.bb1:                                           ; preds = %entry, %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !370
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !371
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @doctype1, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !372
  store i32 4, i32* %retval, align 4, !dbg !373
  br label %return, !dbg !373

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !374
  %3 = load i32, i32* %tok.addr, align 4, !dbg !375
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !376
  store i32 %call, i32* %retval, align 4, !dbg !377
  br label %return, !dbg !377

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !378
  ret i32 %4, !dbg !378
}

; Function Attrs: nounwind uwtable
define internal i32 @error(%struct.prolog_state* %UNUSED_state, i32 %UNUSED_tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !220 {
entry:
  %UNUSED_state.addr = alloca %struct.prolog_state*, align 8
  %UNUSED_tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %UNUSED_state, %struct.prolog_state** %UNUSED_state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %UNUSED_state.addr, metadata !379, metadata !269), !dbg !380
  store i32 %UNUSED_tok, i32* %UNUSED_tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %UNUSED_tok.addr, metadata !381, metadata !269), !dbg !382
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !383, metadata !269), !dbg !384
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !385, metadata !269), !dbg !386
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !387, metadata !269), !dbg !388
  ret i32 0, !dbg !389
}

; Function Attrs: nounwind uwtable
define internal i32 @common(%struct.prolog_state* %state, i32 %tok) #0 !dbg !221 {
entry:
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !390, metadata !269), !dbg !391
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !392, metadata !269), !dbg !393
  %0 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !394
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %0, i32 0, i32 0, !dbg !395
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @error, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !396
  ret i32 -1, !dbg !397
}

; Function Attrs: nounwind uwtable
define internal i32 @doctype1(%struct.prolog_state* %state, i32 %tok, i8* %ptr, i8* %end, %struct.encoding* %enc) #0 !dbg !178 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %end.addr = alloca i8*, align 8
  %enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !398, metadata !269), !dbg !399
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !400, metadata !269), !dbg !401
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !402, metadata !269), !dbg !403
  store i8* %end, i8** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %end.addr, metadata !404, metadata !269), !dbg !405
  store %struct.encoding* %enc, %struct.encoding** %enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %enc.addr, metadata !406, metadata !269), !dbg !407
  %0 = load i32, i32* %tok.addr, align 4, !dbg !408
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 25, label %sw.bb1
    i32 17, label %sw.bb2
    i32 18, label %sw.bb4
  ], !dbg !409

sw.bb:                                            ; preds = %entry
  store i32 3, i32* %retval, align 4, !dbg !410
  br label %return, !dbg !410

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !412
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !413
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @internalSubset, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !414
  store i32 7, i32* %retval, align 4, !dbg !415
  br label %return, !dbg !415

sw.bb2:                                           ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !416
  %handler3 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %2, i32 0, i32 0, !dbg !417
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @prolog2, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler3, align 8, !dbg !418
  store i32 8, i32* %retval, align 4, !dbg !419
  br label %return, !dbg !419

sw.bb4:                                           ; preds = %entry
  %3 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !420
  %nameMatchesAscii = getelementptr inbounds %struct.encoding, %struct.encoding* %3, i32 0, i32 3, !dbg !420
  %4 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii, align 8, !dbg !420
  %5 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !420
  %6 = load i8*, i8** %ptr.addr, align 8, !dbg !420
  %7 = load i8*, i8** %end.addr, align 8, !dbg !420
  %call = call i32 %4(%struct.encoding* %5, i8* %6, i8* %7, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @KW_SYSTEM, i32 0, i32 0)), !dbg !420
  %tobool = icmp ne i32 %call, 0, !dbg !420
  br i1 %tobool, label %if.then, label %if.end, !dbg !422

if.then:                                          ; preds = %sw.bb4
  %8 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !423
  %handler5 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %8, i32 0, i32 0, !dbg !425
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @doctype3, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler5, align 8, !dbg !426
  store i32 3, i32* %retval, align 4, !dbg !427
  br label %return, !dbg !427

if.end:                                           ; preds = %sw.bb4
  %9 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !428
  %nameMatchesAscii6 = getelementptr inbounds %struct.encoding, %struct.encoding* %9, i32 0, i32 3, !dbg !428
  %10 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii6, align 8, !dbg !428
  %11 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !428
  %12 = load i8*, i8** %ptr.addr, align 8, !dbg !428
  %13 = load i8*, i8** %end.addr, align 8, !dbg !428
  %call7 = call i32 %10(%struct.encoding* %11, i8* %12, i8* %13, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @KW_PUBLIC, i32 0, i32 0)), !dbg !428
  %tobool8 = icmp ne i32 %call7, 0, !dbg !428
  br i1 %tobool8, label %if.then9, label %if.end11, !dbg !430

if.then9:                                         ; preds = %if.end
  %14 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !431
  %handler10 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %14, i32 0, i32 0, !dbg !433
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @doctype2, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler10, align 8, !dbg !434
  store i32 3, i32* %retval, align 4, !dbg !435
  br label %return, !dbg !435

if.end11:                                         ; preds = %if.end
  br label %sw.epilog, !dbg !436

sw.epilog:                                        ; preds = %entry, %if.end11
  %15 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !437
  %16 = load i32, i32* %tok.addr, align 4, !dbg !438
  %call12 = call i32 @common(%struct.prolog_state* %15, i32 %16), !dbg !439
  store i32 %call12, i32* %retval, align 4, !dbg !440
  br label %return, !dbg !440

return:                                           ; preds = %sw.epilog, %if.then9, %if.then, %sw.bb2, %sw.bb1, %sw.bb
  %17 = load i32, i32* %retval, align 4, !dbg !441
  ret i32 %17, !dbg !441
}

; Function Attrs: nounwind uwtable
define internal i32 @internalSubset(%struct.prolog_state* %state, i32 %tok, i8* %ptr, i8* %end, %struct.encoding* %enc) #0 !dbg !179 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %end.addr = alloca i8*, align 8
  %enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !442, metadata !269), !dbg !443
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !444, metadata !269), !dbg !445
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !446, metadata !269), !dbg !447
  store i8* %end, i8** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %end.addr, metadata !448, metadata !269), !dbg !449
  store %struct.encoding* %enc, %struct.encoding** %enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %enc.addr, metadata !450, metadata !269), !dbg !451
  %0 = load i32, i32* %tok.addr, align 4, !dbg !452
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 16, label %sw.bb1
    i32 11, label %sw.bb32
    i32 13, label %sw.bb33
    i32 28, label %sw.bb34
    i32 26, label %sw.bb35
    i32 -4, label %sw.bb37
  ], !dbg !453

sw.bb:                                            ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !454
  br label %return, !dbg !454

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !456
  %nameMatchesAscii = getelementptr inbounds %struct.encoding, %struct.encoding* %1, i32 0, i32 3, !dbg !456
  %2 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii, align 8, !dbg !456
  %3 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !456
  %4 = load i8*, i8** %ptr.addr, align 8, !dbg !456
  %5 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !456
  %minBytesPerChar = getelementptr inbounds %struct.encoding, %struct.encoding* %5, i32 0, i32 13, !dbg !456
  %6 = load i32, i32* %minBytesPerChar, align 8, !dbg !456
  %mul = mul nsw i32 2, %6, !dbg !456
  %idx.ext = sext i32 %mul to i64, !dbg !456
  %add.ptr = getelementptr inbounds i8, i8* %4, i64 %idx.ext, !dbg !456
  %7 = load i8*, i8** %end.addr, align 8, !dbg !456
  %call = call i32 %2(%struct.encoding* %3, i8* %add.ptr, i8* %7, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @KW_ENTITY, i32 0, i32 0)), !dbg !456
  %tobool = icmp ne i32 %call, 0, !dbg !456
  br i1 %tobool, label %if.then, label %if.end, !dbg !458

if.then:                                          ; preds = %sw.bb1
  %8 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !459
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %8, i32 0, i32 0, !dbg !461
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @entity0, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !462
  store i32 11, i32* %retval, align 4, !dbg !463
  br label %return, !dbg !463

if.end:                                           ; preds = %sw.bb1
  %9 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !464
  %nameMatchesAscii2 = getelementptr inbounds %struct.encoding, %struct.encoding* %9, i32 0, i32 3, !dbg !464
  %10 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii2, align 8, !dbg !464
  %11 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !464
  %12 = load i8*, i8** %ptr.addr, align 8, !dbg !464
  %13 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !464
  %minBytesPerChar3 = getelementptr inbounds %struct.encoding, %struct.encoding* %13, i32 0, i32 13, !dbg !464
  %14 = load i32, i32* %minBytesPerChar3, align 8, !dbg !464
  %mul4 = mul nsw i32 2, %14, !dbg !464
  %idx.ext5 = sext i32 %mul4 to i64, !dbg !464
  %add.ptr6 = getelementptr inbounds i8, i8* %12, i64 %idx.ext5, !dbg !464
  %15 = load i8*, i8** %end.addr, align 8, !dbg !464
  %call7 = call i32 %10(%struct.encoding* %11, i8* %add.ptr6, i8* %15, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @KW_ATTLIST, i32 0, i32 0)), !dbg !464
  %tobool8 = icmp ne i32 %call7, 0, !dbg !464
  br i1 %tobool8, label %if.then9, label %if.end11, !dbg !466

if.then9:                                         ; preds = %if.end
  %16 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !467
  %handler10 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %16, i32 0, i32 0, !dbg !469
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist0, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler10, align 8, !dbg !470
  store i32 33, i32* %retval, align 4, !dbg !471
  br label %return, !dbg !471

if.end11:                                         ; preds = %if.end
  %17 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !472
  %nameMatchesAscii12 = getelementptr inbounds %struct.encoding, %struct.encoding* %17, i32 0, i32 3, !dbg !472
  %18 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii12, align 8, !dbg !472
  %19 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !472
  %20 = load i8*, i8** %ptr.addr, align 8, !dbg !472
  %21 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !472
  %minBytesPerChar13 = getelementptr inbounds %struct.encoding, %struct.encoding* %21, i32 0, i32 13, !dbg !472
  %22 = load i32, i32* %minBytesPerChar13, align 8, !dbg !472
  %mul14 = mul nsw i32 2, %22, !dbg !472
  %idx.ext15 = sext i32 %mul14 to i64, !dbg !472
  %add.ptr16 = getelementptr inbounds i8, i8* %20, i64 %idx.ext15, !dbg !472
  %23 = load i8*, i8** %end.addr, align 8, !dbg !472
  %call17 = call i32 %18(%struct.encoding* %19, i8* %add.ptr16, i8* %23, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @KW_ELEMENT, i32 0, i32 0)), !dbg !472
  %tobool18 = icmp ne i32 %call17, 0, !dbg !472
  br i1 %tobool18, label %if.then19, label %if.end21, !dbg !474

if.then19:                                        ; preds = %if.end11
  %24 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !475
  %handler20 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %24, i32 0, i32 0, !dbg !477
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element0, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler20, align 8, !dbg !478
  store i32 39, i32* %retval, align 4, !dbg !479
  br label %return, !dbg !479

if.end21:                                         ; preds = %if.end11
  %25 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !480
  %nameMatchesAscii22 = getelementptr inbounds %struct.encoding, %struct.encoding* %25, i32 0, i32 3, !dbg !480
  %26 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii22, align 8, !dbg !480
  %27 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !480
  %28 = load i8*, i8** %ptr.addr, align 8, !dbg !480
  %29 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !480
  %minBytesPerChar23 = getelementptr inbounds %struct.encoding, %struct.encoding* %29, i32 0, i32 13, !dbg !480
  %30 = load i32, i32* %minBytesPerChar23, align 8, !dbg !480
  %mul24 = mul nsw i32 2, %30, !dbg !480
  %idx.ext25 = sext i32 %mul24 to i64, !dbg !480
  %add.ptr26 = getelementptr inbounds i8, i8* %28, i64 %idx.ext25, !dbg !480
  %31 = load i8*, i8** %end.addr, align 8, !dbg !480
  %call27 = call i32 %26(%struct.encoding* %27, i8* %add.ptr26, i8* %31, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @KW_NOTATION, i32 0, i32 0)), !dbg !480
  %tobool28 = icmp ne i32 %call27, 0, !dbg !480
  br i1 %tobool28, label %if.then29, label %if.end31, !dbg !482

if.then29:                                        ; preds = %if.end21
  %32 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !483
  %handler30 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %32, i32 0, i32 0, !dbg !485
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @notation0, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler30, align 8, !dbg !486
  store i32 17, i32* %retval, align 4, !dbg !487
  br label %return, !dbg !487

if.end31:                                         ; preds = %if.end21
  br label %sw.epilog, !dbg !488

sw.bb32:                                          ; preds = %entry
  store i32 55, i32* %retval, align 4, !dbg !489
  br label %return, !dbg !489

sw.bb33:                                          ; preds = %entry
  store i32 56, i32* %retval, align 4, !dbg !490
  br label %return, !dbg !490

sw.bb34:                                          ; preds = %entry
  store i32 57, i32* %retval, align 4, !dbg !491
  br label %return, !dbg !491

sw.bb35:                                          ; preds = %entry
  %33 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !492
  %handler36 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %33, i32 0, i32 0, !dbg !493
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @doctype5, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler36, align 8, !dbg !494
  store i32 3, i32* %retval, align 4, !dbg !495
  br label %return, !dbg !495

sw.bb37:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !496
  br label %return, !dbg !496

sw.epilog:                                        ; preds = %entry, %if.end31
  %34 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !497
  %35 = load i32, i32* %tok.addr, align 4, !dbg !498
  %call38 = call i32 @common(%struct.prolog_state* %34, i32 %35), !dbg !499
  store i32 %call38, i32* %retval, align 4, !dbg !500
  br label %return, !dbg !500

return:                                           ; preds = %sw.epilog, %sw.bb37, %sw.bb35, %sw.bb34, %sw.bb33, %sw.bb32, %if.then29, %if.then19, %if.then9, %if.then, %sw.bb
  %36 = load i32, i32* %retval, align 4, !dbg !501
  ret i32 %36, !dbg !501
}

; Function Attrs: nounwind uwtable
define internal i32 @prolog2(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !216 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !502, metadata !269), !dbg !503
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !504, metadata !269), !dbg !505
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !506, metadata !269), !dbg !507
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !508, metadata !269), !dbg !509
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !510, metadata !269), !dbg !511
  %0 = load i32, i32* %tok.addr, align 4, !dbg !512
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 11, label %sw.bb1
    i32 13, label %sw.bb2
    i32 29, label %sw.bb3
  ], !dbg !513

sw.bb:                                            ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !514
  br label %return, !dbg !514

sw.bb1:                                           ; preds = %entry
  store i32 55, i32* %retval, align 4, !dbg !516
  br label %return, !dbg !516

sw.bb2:                                           ; preds = %entry
  store i32 56, i32* %retval, align 4, !dbg !517
  br label %return, !dbg !517

sw.bb3:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !518
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !519
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @error, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !520
  store i32 2, i32* %retval, align 4, !dbg !521
  br label %return, !dbg !521

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !522
  %3 = load i32, i32* %tok.addr, align 4, !dbg !523
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !524
  store i32 %call, i32* %retval, align 4, !dbg !525
  br label %return, !dbg !525

return:                                           ; preds = %sw.epilog, %sw.bb3, %sw.bb2, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !526
  ret i32 %4, !dbg !526
}

; Function Attrs: nounwind uwtable
define internal i32 @doctype3(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !217 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !527, metadata !269), !dbg !528
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !529, metadata !269), !dbg !530
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !531, metadata !269), !dbg !532
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !533, metadata !269), !dbg !534
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !535, metadata !269), !dbg !536
  %0 = load i32, i32* %tok.addr, align 4, !dbg !537
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 27, label %sw.bb1
  ], !dbg !538

sw.bb:                                            ; preds = %entry
  store i32 3, i32* %retval, align 4, !dbg !539
  br label %return, !dbg !539

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !541
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !542
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @doctype4, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !543
  store i32 5, i32* %retval, align 4, !dbg !544
  br label %return, !dbg !544

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !545
  %3 = load i32, i32* %tok.addr, align 4, !dbg !546
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !547
  store i32 %call, i32* %retval, align 4, !dbg !548
  br label %return, !dbg !548

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !549
  ret i32 %4, !dbg !549
}

; Function Attrs: nounwind uwtable
define internal i32 @doctype2(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !219 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !550, metadata !269), !dbg !551
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !552, metadata !269), !dbg !553
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !554, metadata !269), !dbg !555
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !556, metadata !269), !dbg !557
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !558, metadata !269), !dbg !559
  %0 = load i32, i32* %tok.addr, align 4, !dbg !560
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 27, label %sw.bb1
  ], !dbg !561

sw.bb:                                            ; preds = %entry
  store i32 3, i32* %retval, align 4, !dbg !562
  br label %return, !dbg !562

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !564
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !565
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @doctype3, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !566
  store i32 6, i32* %retval, align 4, !dbg !567
  br label %return, !dbg !567

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !568
  %3 = load i32, i32* %tok.addr, align 4, !dbg !569
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !570
  store i32 %call, i32* %retval, align 4, !dbg !571
  br label %return, !dbg !571

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !572
  ret i32 %4, !dbg !572
}

; Function Attrs: nounwind uwtable
define internal i32 @entity0(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !180 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !573, metadata !269), !dbg !574
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !575, metadata !269), !dbg !576
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !577, metadata !269), !dbg !578
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !579, metadata !269), !dbg !580
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !581, metadata !269), !dbg !582
  %0 = load i32, i32* %tok.addr, align 4, !dbg !583
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 22, label %sw.bb1
    i32 18, label %sw.bb2
  ], !dbg !584

sw.bb:                                            ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !585
  br label %return, !dbg !585

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !587
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !588
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @entity1, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !589
  store i32 11, i32* %retval, align 4, !dbg !590
  br label %return, !dbg !590

sw.bb2:                                           ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !591
  %handler3 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %2, i32 0, i32 0, !dbg !592
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @entity2, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler3, align 8, !dbg !593
  store i32 9, i32* %retval, align 4, !dbg !594
  br label %return, !dbg !594

sw.epilog:                                        ; preds = %entry
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !595
  %4 = load i32, i32* %tok.addr, align 4, !dbg !596
  %call = call i32 @common(%struct.prolog_state* %3, i32 %4), !dbg !597
  store i32 %call, i32* %retval, align 4, !dbg !598
  br label %return, !dbg !598

return:                                           ; preds = %sw.epilog, %sw.bb2, %sw.bb1, %sw.bb
  %5 = load i32, i32* %retval, align 4, !dbg !599
  ret i32 %5, !dbg !599
}

; Function Attrs: nounwind uwtable
define internal i32 @attlist0(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !192 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !600, metadata !269), !dbg !601
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !602, metadata !269), !dbg !603
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !604, metadata !269), !dbg !605
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !606, metadata !269), !dbg !607
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !608, metadata !269), !dbg !609
  %0 = load i32, i32* %tok.addr, align 4, !dbg !610
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 18, label %sw.bb1
    i32 41, label %sw.bb1
  ], !dbg !611

sw.bb:                                            ; preds = %entry
  store i32 33, i32* %retval, align 4, !dbg !612
  br label %return, !dbg !612

sw.bb1:                                           ; preds = %entry, %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !614
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !615
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist1, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !616
  store i32 34, i32* %retval, align 4, !dbg !617
  br label %return, !dbg !617

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !618
  %3 = load i32, i32* %tok.addr, align 4, !dbg !619
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !620
  store i32 %call, i32* %retval, align 4, !dbg !621
  br label %return, !dbg !621

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !622
  ret i32 %4, !dbg !622
}

; Function Attrs: nounwind uwtable
define internal i32 @element0(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !202 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !623, metadata !269), !dbg !624
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !625, metadata !269), !dbg !626
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !627, metadata !269), !dbg !628
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !629, metadata !269), !dbg !630
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !631, metadata !269), !dbg !632
  %0 = load i32, i32* %tok.addr, align 4, !dbg !633
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 18, label %sw.bb1
    i32 41, label %sw.bb1
  ], !dbg !634

sw.bb:                                            ; preds = %entry
  store i32 39, i32* %retval, align 4, !dbg !635
  br label %return, !dbg !635

sw.bb1:                                           ; preds = %entry, %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !637
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !638
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element1, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !639
  store i32 40, i32* %retval, align 4, !dbg !640
  br label %return, !dbg !640

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !641
  %3 = load i32, i32* %tok.addr, align 4, !dbg !642
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !643
  store i32 %call, i32* %retval, align 4, !dbg !644
  br label %return, !dbg !644

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !645
  ret i32 %4, !dbg !645
}

; Function Attrs: nounwind uwtable
define internal i32 @notation0(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !210 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !646, metadata !269), !dbg !647
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !648, metadata !269), !dbg !649
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !650, metadata !269), !dbg !651
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !652, metadata !269), !dbg !653
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !654, metadata !269), !dbg !655
  %0 = load i32, i32* %tok.addr, align 4, !dbg !656
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 18, label %sw.bb1
  ], !dbg !657

sw.bb:                                            ; preds = %entry
  store i32 17, i32* %retval, align 4, !dbg !658
  br label %return, !dbg !658

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !660
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !661
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @notation1, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !662
  store i32 18, i32* %retval, align 4, !dbg !663
  br label %return, !dbg !663

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !664
  %3 = load i32, i32* %tok.addr, align 4, !dbg !665
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !666
  store i32 %call, i32* %retval, align 4, !dbg !667
  br label %return, !dbg !667

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !668
  ret i32 %4, !dbg !668
}

; Function Attrs: nounwind uwtable
define internal i32 @doctype5(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !215 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !669, metadata !269), !dbg !670
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !671, metadata !269), !dbg !672
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !673, metadata !269), !dbg !674
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !675, metadata !269), !dbg !676
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !677, metadata !269), !dbg !678
  %0 = load i32, i32* %tok.addr, align 4, !dbg !679
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 17, label %sw.bb1
  ], !dbg !680

sw.bb:                                            ; preds = %entry
  store i32 3, i32* %retval, align 4, !dbg !681
  br label %return, !dbg !681

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !683
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !684
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @prolog2, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !685
  store i32 8, i32* %retval, align 4, !dbg !686
  br label %return, !dbg !686

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !687
  %3 = load i32, i32* %tok.addr, align 4, !dbg !688
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !689
  store i32 %call, i32* %retval, align 4, !dbg !690
  br label %return, !dbg !690

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !691
  ret i32 %4, !dbg !691
}

; Function Attrs: nounwind uwtable
define internal i32 @entity1(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !181 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !692, metadata !269), !dbg !693
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !694, metadata !269), !dbg !695
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !696, metadata !269), !dbg !697
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !698, metadata !269), !dbg !699
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !700, metadata !269), !dbg !701
  %0 = load i32, i32* %tok.addr, align 4, !dbg !702
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 18, label %sw.bb1
  ], !dbg !703

sw.bb:                                            ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !704
  br label %return, !dbg !704

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !706
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !707
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @entity7, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !708
  store i32 10, i32* %retval, align 4, !dbg !709
  br label %return, !dbg !709

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !710
  %3 = load i32, i32* %tok.addr, align 4, !dbg !711
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !712
  store i32 %call, i32* %retval, align 4, !dbg !713
  br label %return, !dbg !713

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !714
  ret i32 %4, !dbg !714
}

; Function Attrs: nounwind uwtable
define internal i32 @entity2(%struct.prolog_state* %state, i32 %tok, i8* %ptr, i8* %end, %struct.encoding* %enc) #0 !dbg !187 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %end.addr = alloca i8*, align 8
  %enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !715, metadata !269), !dbg !716
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !717, metadata !269), !dbg !718
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !719, metadata !269), !dbg !720
  store i8* %end, i8** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %end.addr, metadata !721, metadata !269), !dbg !722
  store %struct.encoding* %enc, %struct.encoding** %enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %enc.addr, metadata !723, metadata !269), !dbg !724
  %0 = load i32, i32* %tok.addr, align 4, !dbg !725
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 18, label %sw.bb1
    i32 27, label %sw.bb8
  ], !dbg !726

sw.bb:                                            ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !727
  br label %return, !dbg !727

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !729
  %nameMatchesAscii = getelementptr inbounds %struct.encoding, %struct.encoding* %1, i32 0, i32 3, !dbg !729
  %2 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii, align 8, !dbg !729
  %3 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !729
  %4 = load i8*, i8** %ptr.addr, align 8, !dbg !729
  %5 = load i8*, i8** %end.addr, align 8, !dbg !729
  %call = call i32 %2(%struct.encoding* %3, i8* %4, i8* %5, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @KW_SYSTEM, i32 0, i32 0)), !dbg !729
  %tobool = icmp ne i32 %call, 0, !dbg !729
  br i1 %tobool, label %if.then, label %if.end, !dbg !731

if.then:                                          ; preds = %sw.bb1
  %6 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !732
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %6, i32 0, i32 0, !dbg !734
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @entity4, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !735
  store i32 11, i32* %retval, align 4, !dbg !736
  br label %return, !dbg !736

if.end:                                           ; preds = %sw.bb1
  %7 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !737
  %nameMatchesAscii2 = getelementptr inbounds %struct.encoding, %struct.encoding* %7, i32 0, i32 3, !dbg !737
  %8 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii2, align 8, !dbg !737
  %9 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !737
  %10 = load i8*, i8** %ptr.addr, align 8, !dbg !737
  %11 = load i8*, i8** %end.addr, align 8, !dbg !737
  %call3 = call i32 %8(%struct.encoding* %9, i8* %10, i8* %11, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @KW_PUBLIC, i32 0, i32 0)), !dbg !737
  %tobool4 = icmp ne i32 %call3, 0, !dbg !737
  br i1 %tobool4, label %if.then5, label %if.end7, !dbg !739

if.then5:                                         ; preds = %if.end
  %12 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !740
  %handler6 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %12, i32 0, i32 0, !dbg !742
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @entity3, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler6, align 8, !dbg !743
  store i32 11, i32* %retval, align 4, !dbg !744
  br label %return, !dbg !744

if.end7:                                          ; preds = %if.end
  br label %sw.epilog, !dbg !745

sw.bb8:                                           ; preds = %entry
  %13 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !746
  %handler9 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %13, i32 0, i32 0, !dbg !747
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler9, align 8, !dbg !748
  %14 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !749
  %role_none = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %14, i32 0, i32 2, !dbg !750
  store i32 11, i32* %role_none, align 4, !dbg !751
  store i32 12, i32* %retval, align 4, !dbg !752
  br label %return, !dbg !752

sw.epilog:                                        ; preds = %entry, %if.end7
  %15 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !753
  %16 = load i32, i32* %tok.addr, align 4, !dbg !754
  %call10 = call i32 @common(%struct.prolog_state* %15, i32 %16), !dbg !755
  store i32 %call10, i32* %retval, align 4, !dbg !756
  br label %return, !dbg !756

return:                                           ; preds = %sw.epilog, %sw.bb8, %if.then5, %if.then, %sw.bb
  %17 = load i32, i32* %retval, align 4, !dbg !757
  ret i32 %17, !dbg !757
}

; Function Attrs: nounwind uwtable
define internal i32 @entity7(%struct.prolog_state* %state, i32 %tok, i8* %ptr, i8* %end, %struct.encoding* %enc) #0 !dbg !182 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %end.addr = alloca i8*, align 8
  %enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !758, metadata !269), !dbg !759
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !760, metadata !269), !dbg !761
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !762, metadata !269), !dbg !763
  store i8* %end, i8** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %end.addr, metadata !764, metadata !269), !dbg !765
  store %struct.encoding* %enc, %struct.encoding** %enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %enc.addr, metadata !766, metadata !269), !dbg !767
  %0 = load i32, i32* %tok.addr, align 4, !dbg !768
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 18, label %sw.bb1
    i32 27, label %sw.bb8
  ], !dbg !769

sw.bb:                                            ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !770
  br label %return, !dbg !770

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !772
  %nameMatchesAscii = getelementptr inbounds %struct.encoding, %struct.encoding* %1, i32 0, i32 3, !dbg !772
  %2 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii, align 8, !dbg !772
  %3 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !772
  %4 = load i8*, i8** %ptr.addr, align 8, !dbg !772
  %5 = load i8*, i8** %end.addr, align 8, !dbg !772
  %call = call i32 %2(%struct.encoding* %3, i8* %4, i8* %5, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @KW_SYSTEM, i32 0, i32 0)), !dbg !772
  %tobool = icmp ne i32 %call, 0, !dbg !772
  br i1 %tobool, label %if.then, label %if.end, !dbg !774

if.then:                                          ; preds = %sw.bb1
  %6 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !775
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %6, i32 0, i32 0, !dbg !777
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @entity9, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !778
  store i32 11, i32* %retval, align 4, !dbg !779
  br label %return, !dbg !779

if.end:                                           ; preds = %sw.bb1
  %7 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !780
  %nameMatchesAscii2 = getelementptr inbounds %struct.encoding, %struct.encoding* %7, i32 0, i32 3, !dbg !780
  %8 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii2, align 8, !dbg !780
  %9 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !780
  %10 = load i8*, i8** %ptr.addr, align 8, !dbg !780
  %11 = load i8*, i8** %end.addr, align 8, !dbg !780
  %call3 = call i32 %8(%struct.encoding* %9, i8* %10, i8* %11, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @KW_PUBLIC, i32 0, i32 0)), !dbg !780
  %tobool4 = icmp ne i32 %call3, 0, !dbg !780
  br i1 %tobool4, label %if.then5, label %if.end7, !dbg !782

if.then5:                                         ; preds = %if.end
  %12 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !783
  %handler6 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %12, i32 0, i32 0, !dbg !785
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @entity8, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler6, align 8, !dbg !786
  store i32 11, i32* %retval, align 4, !dbg !787
  br label %return, !dbg !787

if.end7:                                          ; preds = %if.end
  br label %sw.epilog, !dbg !788

sw.bb8:                                           ; preds = %entry
  %13 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !789
  %handler9 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %13, i32 0, i32 0, !dbg !790
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler9, align 8, !dbg !791
  %14 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !792
  %role_none = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %14, i32 0, i32 2, !dbg !793
  store i32 11, i32* %role_none, align 4, !dbg !794
  store i32 12, i32* %retval, align 4, !dbg !795
  br label %return, !dbg !795

sw.epilog:                                        ; preds = %entry, %if.end7
  %15 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !796
  %16 = load i32, i32* %tok.addr, align 4, !dbg !797
  %call10 = call i32 @common(%struct.prolog_state* %15, i32 %16), !dbg !798
  store i32 %call10, i32* %retval, align 4, !dbg !799
  br label %return, !dbg !799

return:                                           ; preds = %sw.epilog, %sw.bb8, %if.then5, %if.then, %sw.bb
  %17 = load i32, i32* %retval, align 4, !dbg !800
  ret i32 %17, !dbg !800
}

; Function Attrs: nounwind uwtable
define internal i32 @entity9(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !183 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !801, metadata !269), !dbg !802
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !803, metadata !269), !dbg !804
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !805, metadata !269), !dbg !806
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !807, metadata !269), !dbg !808
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !809, metadata !269), !dbg !810
  %0 = load i32, i32* %tok.addr, align 4, !dbg !811
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 27, label %sw.bb1
  ], !dbg !812

sw.bb:                                            ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !813
  br label %return, !dbg !813

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !815
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !816
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @entity10, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !817
  store i32 13, i32* %retval, align 4, !dbg !818
  br label %return, !dbg !818

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !819
  %3 = load i32, i32* %tok.addr, align 4, !dbg !820
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !821
  store i32 %call, i32* %retval, align 4, !dbg !822
  br label %return, !dbg !822

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !823
  ret i32 %4, !dbg !823
}

; Function Attrs: nounwind uwtable
define internal i32 @entity8(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !185 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !824, metadata !269), !dbg !825
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !826, metadata !269), !dbg !827
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !828, metadata !269), !dbg !829
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !830, metadata !269), !dbg !831
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !832, metadata !269), !dbg !833
  %0 = load i32, i32* %tok.addr, align 4, !dbg !834
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 27, label %sw.bb1
  ], !dbg !835

sw.bb:                                            ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !836
  br label %return, !dbg !836

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !838
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !839
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @entity9, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !840
  store i32 14, i32* %retval, align 4, !dbg !841
  br label %return, !dbg !841

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !842
  %3 = load i32, i32* %tok.addr, align 4, !dbg !843
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !844
  store i32 %call, i32* %retval, align 4, !dbg !845
  br label %return, !dbg !845

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !846
  ret i32 %4, !dbg !846
}

; Function Attrs: nounwind uwtable
define internal i32 @declClose(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !186 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !847, metadata !269), !dbg !848
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !849, metadata !269), !dbg !850
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !851, metadata !269), !dbg !852
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !853, metadata !269), !dbg !854
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !855, metadata !269), !dbg !856
  %0 = load i32, i32* %tok.addr, align 4, !dbg !857
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 17, label %sw.bb1
  ], !dbg !858

sw.bb:                                            ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !859
  %role_none = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 2, !dbg !861
  %2 = load i32, i32* %role_none, align 4, !dbg !861
  store i32 %2, i32* %retval, align 4, !dbg !862
  br label %return, !dbg !862

sw.bb1:                                           ; preds = %entry
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !863
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %3, i32 0, i32 0, !dbg !863
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @internalSubset, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !863
  %4 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !864
  %role_none2 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %4, i32 0, i32 2, !dbg !865
  %5 = load i32, i32* %role_none2, align 4, !dbg !865
  store i32 %5, i32* %retval, align 4, !dbg !866
  br label %return, !dbg !866

sw.epilog:                                        ; preds = %entry
  %6 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !867
  %7 = load i32, i32* %tok.addr, align 4, !dbg !868
  %call = call i32 @common(%struct.prolog_state* %6, i32 %7), !dbg !869
  store i32 %call, i32* %retval, align 4, !dbg !870
  br label %return, !dbg !870

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %8 = load i32, i32* %retval, align 4, !dbg !871
  ret i32 %8, !dbg !871
}

; Function Attrs: nounwind uwtable
define internal i32 @entity10(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !184 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !872, metadata !269), !dbg !873
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !874, metadata !269), !dbg !875
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !876, metadata !269), !dbg !877
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !878, metadata !269), !dbg !879
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !880, metadata !269), !dbg !881
  %0 = load i32, i32* %tok.addr, align 4, !dbg !882
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 17, label %sw.bb1
  ], !dbg !883

sw.bb:                                            ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !884
  br label %return, !dbg !884

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !886
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !886
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @internalSubset, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !886
  store i32 15, i32* %retval, align 4, !dbg !887
  br label %return, !dbg !887

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !888
  %3 = load i32, i32* %tok.addr, align 4, !dbg !889
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !890
  store i32 %call, i32* %retval, align 4, !dbg !891
  br label %return, !dbg !891

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !892
  ret i32 %4, !dbg !892
}

; Function Attrs: nounwind uwtable
define internal i32 @entity4(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !188 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !893, metadata !269), !dbg !894
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !895, metadata !269), !dbg !896
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !897, metadata !269), !dbg !898
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !899, metadata !269), !dbg !900
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !901, metadata !269), !dbg !902
  %0 = load i32, i32* %tok.addr, align 4, !dbg !903
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 27, label %sw.bb1
  ], !dbg !904

sw.bb:                                            ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !905
  br label %return, !dbg !905

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !907
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !908
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @entity5, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !909
  store i32 13, i32* %retval, align 4, !dbg !910
  br label %return, !dbg !910

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !911
  %3 = load i32, i32* %tok.addr, align 4, !dbg !912
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !913
  store i32 %call, i32* %retval, align 4, !dbg !914
  br label %return, !dbg !914

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !915
  ret i32 %4, !dbg !915
}

; Function Attrs: nounwind uwtable
define internal i32 @entity3(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !191 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !916, metadata !269), !dbg !917
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !918, metadata !269), !dbg !919
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !920, metadata !269), !dbg !921
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !922, metadata !269), !dbg !923
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !924, metadata !269), !dbg !925
  %0 = load i32, i32* %tok.addr, align 4, !dbg !926
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 27, label %sw.bb1
  ], !dbg !927

sw.bb:                                            ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !928
  br label %return, !dbg !928

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !930
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !931
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @entity4, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !932
  store i32 14, i32* %retval, align 4, !dbg !933
  br label %return, !dbg !933

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !934
  %3 = load i32, i32* %tok.addr, align 4, !dbg !935
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !936
  store i32 %call, i32* %retval, align 4, !dbg !937
  br label %return, !dbg !937

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !938
  ret i32 %4, !dbg !938
}

; Function Attrs: nounwind uwtable
define internal i32 @entity5(%struct.prolog_state* %state, i32 %tok, i8* %ptr, i8* %end, %struct.encoding* %enc) #0 !dbg !189 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %end.addr = alloca i8*, align 8
  %enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !939, metadata !269), !dbg !940
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !941, metadata !269), !dbg !942
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !943, metadata !269), !dbg !944
  store i8* %end, i8** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %end.addr, metadata !945, metadata !269), !dbg !946
  store %struct.encoding* %enc, %struct.encoding** %enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %enc.addr, metadata !947, metadata !269), !dbg !948
  %0 = load i32, i32* %tok.addr, align 4, !dbg !949
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 17, label %sw.bb1
    i32 18, label %sw.bb2
  ], !dbg !950

sw.bb:                                            ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !951
  br label %return, !dbg !951

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !953
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !953
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @internalSubset, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !953
  store i32 15, i32* %retval, align 4, !dbg !954
  br label %return, !dbg !954

sw.bb2:                                           ; preds = %entry
  %2 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !955
  %nameMatchesAscii = getelementptr inbounds %struct.encoding, %struct.encoding* %2, i32 0, i32 3, !dbg !955
  %3 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii, align 8, !dbg !955
  %4 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !955
  %5 = load i8*, i8** %ptr.addr, align 8, !dbg !955
  %6 = load i8*, i8** %end.addr, align 8, !dbg !955
  %call = call i32 %3(%struct.encoding* %4, i8* %5, i8* %6, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @KW_NDATA, i32 0, i32 0)), !dbg !955
  %tobool = icmp ne i32 %call, 0, !dbg !955
  br i1 %tobool, label %if.then, label %if.end, !dbg !957

if.then:                                          ; preds = %sw.bb2
  %7 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !958
  %handler3 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %7, i32 0, i32 0, !dbg !960
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @entity6, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler3, align 8, !dbg !961
  store i32 11, i32* %retval, align 4, !dbg !962
  br label %return, !dbg !962

if.end:                                           ; preds = %sw.bb2
  br label %sw.epilog, !dbg !963

sw.epilog:                                        ; preds = %entry, %if.end
  %8 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !964
  %9 = load i32, i32* %tok.addr, align 4, !dbg !965
  %call4 = call i32 @common(%struct.prolog_state* %8, i32 %9), !dbg !966
  store i32 %call4, i32* %retval, align 4, !dbg !967
  br label %return, !dbg !967

return:                                           ; preds = %sw.epilog, %if.then, %sw.bb1, %sw.bb
  %10 = load i32, i32* %retval, align 4, !dbg !968
  ret i32 %10, !dbg !968
}

; Function Attrs: nounwind uwtable
define internal i32 @entity6(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !190 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !969, metadata !269), !dbg !970
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !971, metadata !269), !dbg !972
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !973, metadata !269), !dbg !974
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !975, metadata !269), !dbg !976
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !977, metadata !269), !dbg !978
  %0 = load i32, i32* %tok.addr, align 4, !dbg !979
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 18, label %sw.bb1
  ], !dbg !980

sw.bb:                                            ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !981
  br label %return, !dbg !981

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !983
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !984
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !985
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !986
  %role_none = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %2, i32 0, i32 2, !dbg !987
  store i32 11, i32* %role_none, align 4, !dbg !988
  store i32 16, i32* %retval, align 4, !dbg !989
  br label %return, !dbg !989

sw.epilog:                                        ; preds = %entry
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !990
  %4 = load i32, i32* %tok.addr, align 4, !dbg !991
  %call = call i32 @common(%struct.prolog_state* %3, i32 %4), !dbg !992
  store i32 %call, i32* %retval, align 4, !dbg !993
  br label %return, !dbg !993

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %5 = load i32, i32* %retval, align 4, !dbg !994
  ret i32 %5, !dbg !994
}

; Function Attrs: nounwind uwtable
define internal i32 @attlist1(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !193 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !995, metadata !269), !dbg !996
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !997, metadata !269), !dbg !998
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !999, metadata !269), !dbg !1000
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1001, metadata !269), !dbg !1002
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1003, metadata !269), !dbg !1004
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1005
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 17, label %sw.bb1
    i32 18, label %sw.bb2
    i32 41, label %sw.bb2
  ], !dbg !1006

sw.bb:                                            ; preds = %entry
  store i32 33, i32* %retval, align 4, !dbg !1007
  br label %return, !dbg !1007

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1009
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1009
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @internalSubset, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1009
  store i32 33, i32* %retval, align 4, !dbg !1010
  br label %return, !dbg !1010

sw.bb2:                                           ; preds = %entry, %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1011
  %handler3 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %2, i32 0, i32 0, !dbg !1012
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist2, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler3, align 8, !dbg !1013
  store i32 22, i32* %retval, align 4, !dbg !1014
  br label %return, !dbg !1014

sw.epilog:                                        ; preds = %entry
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1015
  %4 = load i32, i32* %tok.addr, align 4, !dbg !1016
  %call = call i32 @common(%struct.prolog_state* %3, i32 %4), !dbg !1017
  store i32 %call, i32* %retval, align 4, !dbg !1018
  br label %return, !dbg !1018

return:                                           ; preds = %sw.epilog, %sw.bb2, %sw.bb1, %sw.bb
  %5 = load i32, i32* %retval, align 4, !dbg !1019
  ret i32 %5, !dbg !1019
}

; Function Attrs: nounwind uwtable
define internal i32 @attlist2(%struct.prolog_state* %state, i32 %tok, i8* %ptr, i8* %end, %struct.encoding* %enc) #0 !dbg !194 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %end.addr = alloca i8*, align 8
  %enc.addr = alloca %struct.encoding*, align 8
  %i = alloca i32, align 4
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1020, metadata !269), !dbg !1021
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1022, metadata !269), !dbg !1023
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !1024, metadata !269), !dbg !1025
  store i8* %end, i8** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %end.addr, metadata !1026, metadata !269), !dbg !1027
  store %struct.encoding* %enc, %struct.encoding** %enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %enc.addr, metadata !1028, metadata !269), !dbg !1029
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1030
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 18, label %sw.bb1
    i32 23, label %sw.bb8
  ], !dbg !1031

sw.bb:                                            ; preds = %entry
  store i32 33, i32* %retval, align 4, !dbg !1032
  br label %return, !dbg !1032

sw.bb1:                                           ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1034, metadata !269), !dbg !1036
  store i32 0, i32* %i, align 4, !dbg !1037
  br label %for.cond, !dbg !1039

for.cond:                                         ; preds = %for.inc, %sw.bb1
  %1 = load i32, i32* %i, align 4, !dbg !1040
  %cmp = icmp slt i32 %1, 8, !dbg !1043
  br i1 %cmp, label %for.body, label %for.end, !dbg !1044

for.body:                                         ; preds = %for.cond
  %2 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1045
  %nameMatchesAscii = getelementptr inbounds %struct.encoding, %struct.encoding* %2, i32 0, i32 3, !dbg !1045
  %3 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii, align 8, !dbg !1045
  %4 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1045
  %5 = load i8*, i8** %ptr.addr, align 8, !dbg !1045
  %6 = load i8*, i8** %end.addr, align 8, !dbg !1045
  %7 = load i32, i32* %i, align 4, !dbg !1045
  %idxprom = sext i32 %7 to i64, !dbg !1045
  %arrayidx = getelementptr inbounds [8 x i8*], [8 x i8*]* @attlist2.types, i64 0, i64 %idxprom, !dbg !1045
  %8 = load i8*, i8** %arrayidx, align 8, !dbg !1045
  %call = call i32 %3(%struct.encoding* %4, i8* %5, i8* %6, i8* %8), !dbg !1045
  %tobool = icmp ne i32 %call, 0, !dbg !1045
  br i1 %tobool, label %if.then, label %if.end, !dbg !1047

if.then:                                          ; preds = %for.body
  %9 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1048
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %9, i32 0, i32 0, !dbg !1050
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist8, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1051
  %10 = load i32, i32* %i, align 4, !dbg !1052
  %add = add nsw i32 23, %10, !dbg !1053
  store i32 %add, i32* %retval, align 4, !dbg !1054
  br label %return, !dbg !1054

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !1055

for.inc:                                          ; preds = %if.end
  %11 = load i32, i32* %i, align 4, !dbg !1057
  %inc = add nsw i32 %11, 1, !dbg !1057
  store i32 %inc, i32* %i, align 4, !dbg !1057
  br label %for.cond, !dbg !1059

for.end:                                          ; preds = %for.cond
  %12 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1060
  %nameMatchesAscii2 = getelementptr inbounds %struct.encoding, %struct.encoding* %12, i32 0, i32 3, !dbg !1060
  %13 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii2, align 8, !dbg !1060
  %14 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1060
  %15 = load i8*, i8** %ptr.addr, align 8, !dbg !1060
  %16 = load i8*, i8** %end.addr, align 8, !dbg !1060
  %call3 = call i32 %13(%struct.encoding* %14, i8* %15, i8* %16, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @KW_NOTATION, i32 0, i32 0)), !dbg !1060
  %tobool4 = icmp ne i32 %call3, 0, !dbg !1060
  br i1 %tobool4, label %if.then5, label %if.end7, !dbg !1062

if.then5:                                         ; preds = %for.end
  %17 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1063
  %handler6 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %17, i32 0, i32 0, !dbg !1065
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist5, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler6, align 8, !dbg !1066
  store i32 33, i32* %retval, align 4, !dbg !1067
  br label %return, !dbg !1067

if.end7:                                          ; preds = %for.end
  br label %sw.epilog, !dbg !1068

sw.bb8:                                           ; preds = %entry
  %18 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1069
  %handler9 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %18, i32 0, i32 0, !dbg !1070
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist3, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler9, align 8, !dbg !1071
  store i32 33, i32* %retval, align 4, !dbg !1072
  br label %return, !dbg !1072

sw.epilog:                                        ; preds = %entry, %if.end7
  %19 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1073
  %20 = load i32, i32* %tok.addr, align 4, !dbg !1074
  %call10 = call i32 @common(%struct.prolog_state* %19, i32 %20), !dbg !1075
  store i32 %call10, i32* %retval, align 4, !dbg !1076
  br label %return, !dbg !1076

return:                                           ; preds = %sw.epilog, %sw.bb8, %if.then5, %if.then, %sw.bb
  %21 = load i32, i32* %retval, align 4, !dbg !1077
  ret i32 %21, !dbg !1077
}

; Function Attrs: nounwind uwtable
define internal i32 @attlist8(%struct.prolog_state* %state, i32 %tok, i8* %ptr, i8* %end, %struct.encoding* %enc) #0 !dbg !195 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %end.addr = alloca i8*, align 8
  %enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1078, metadata !269), !dbg !1079
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1080, metadata !269), !dbg !1081
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !1082, metadata !269), !dbg !1083
  store i8* %end, i8** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %end.addr, metadata !1084, metadata !269), !dbg !1085
  store %struct.encoding* %enc, %struct.encoding** %enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %enc.addr, metadata !1086, metadata !269), !dbg !1087
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1088
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 20, label %sw.bb1
    i32 27, label %sw.bb20
  ], !dbg !1089

sw.bb:                                            ; preds = %entry
  store i32 33, i32* %retval, align 4, !dbg !1090
  br label %return, !dbg !1090

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1092
  %nameMatchesAscii = getelementptr inbounds %struct.encoding, %struct.encoding* %1, i32 0, i32 3, !dbg !1092
  %2 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii, align 8, !dbg !1092
  %3 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1092
  %4 = load i8*, i8** %ptr.addr, align 8, !dbg !1092
  %5 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1092
  %minBytesPerChar = getelementptr inbounds %struct.encoding, %struct.encoding* %5, i32 0, i32 13, !dbg !1092
  %6 = load i32, i32* %minBytesPerChar, align 8, !dbg !1092
  %idx.ext = sext i32 %6 to i64, !dbg !1092
  %add.ptr = getelementptr inbounds i8, i8* %4, i64 %idx.ext, !dbg !1092
  %7 = load i8*, i8** %end.addr, align 8, !dbg !1092
  %call = call i32 %2(%struct.encoding* %3, i8* %add.ptr, i8* %7, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @KW_IMPLIED, i32 0, i32 0)), !dbg !1092
  %tobool = icmp ne i32 %call, 0, !dbg !1092
  br i1 %tobool, label %if.then, label %if.end, !dbg !1094

if.then:                                          ; preds = %sw.bb1
  %8 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1095
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %8, i32 0, i32 0, !dbg !1097
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist1, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1098
  store i32 35, i32* %retval, align 4, !dbg !1099
  br label %return, !dbg !1099

if.end:                                           ; preds = %sw.bb1
  %9 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1100
  %nameMatchesAscii2 = getelementptr inbounds %struct.encoding, %struct.encoding* %9, i32 0, i32 3, !dbg !1100
  %10 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii2, align 8, !dbg !1100
  %11 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1100
  %12 = load i8*, i8** %ptr.addr, align 8, !dbg !1100
  %13 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1100
  %minBytesPerChar3 = getelementptr inbounds %struct.encoding, %struct.encoding* %13, i32 0, i32 13, !dbg !1100
  %14 = load i32, i32* %minBytesPerChar3, align 8, !dbg !1100
  %idx.ext4 = sext i32 %14 to i64, !dbg !1100
  %add.ptr5 = getelementptr inbounds i8, i8* %12, i64 %idx.ext4, !dbg !1100
  %15 = load i8*, i8** %end.addr, align 8, !dbg !1100
  %call6 = call i32 %10(%struct.encoding* %11, i8* %add.ptr5, i8* %15, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @KW_REQUIRED, i32 0, i32 0)), !dbg !1100
  %tobool7 = icmp ne i32 %call6, 0, !dbg !1100
  br i1 %tobool7, label %if.then8, label %if.end10, !dbg !1102

if.then8:                                         ; preds = %if.end
  %16 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1103
  %handler9 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %16, i32 0, i32 0, !dbg !1105
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist1, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler9, align 8, !dbg !1106
  store i32 36, i32* %retval, align 4, !dbg !1107
  br label %return, !dbg !1107

if.end10:                                         ; preds = %if.end
  %17 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1108
  %nameMatchesAscii11 = getelementptr inbounds %struct.encoding, %struct.encoding* %17, i32 0, i32 3, !dbg !1108
  %18 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii11, align 8, !dbg !1108
  %19 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1108
  %20 = load i8*, i8** %ptr.addr, align 8, !dbg !1108
  %21 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1108
  %minBytesPerChar12 = getelementptr inbounds %struct.encoding, %struct.encoding* %21, i32 0, i32 13, !dbg !1108
  %22 = load i32, i32* %minBytesPerChar12, align 8, !dbg !1108
  %idx.ext13 = sext i32 %22 to i64, !dbg !1108
  %add.ptr14 = getelementptr inbounds i8, i8* %20, i64 %idx.ext13, !dbg !1108
  %23 = load i8*, i8** %end.addr, align 8, !dbg !1108
  %call15 = call i32 %18(%struct.encoding* %19, i8* %add.ptr14, i8* %23, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @KW_FIXED, i32 0, i32 0)), !dbg !1108
  %tobool16 = icmp ne i32 %call15, 0, !dbg !1108
  br i1 %tobool16, label %if.then17, label %if.end19, !dbg !1110

if.then17:                                        ; preds = %if.end10
  %24 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1111
  %handler18 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %24, i32 0, i32 0, !dbg !1113
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist9, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler18, align 8, !dbg !1114
  store i32 33, i32* %retval, align 4, !dbg !1115
  br label %return, !dbg !1115

if.end19:                                         ; preds = %if.end10
  br label %sw.epilog, !dbg !1116

sw.bb20:                                          ; preds = %entry
  %25 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1117
  %handler21 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %25, i32 0, i32 0, !dbg !1118
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist1, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler21, align 8, !dbg !1119
  store i32 37, i32* %retval, align 4, !dbg !1120
  br label %return, !dbg !1120

sw.epilog:                                        ; preds = %entry, %if.end19
  %26 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1121
  %27 = load i32, i32* %tok.addr, align 4, !dbg !1122
  %call22 = call i32 @common(%struct.prolog_state* %26, i32 %27), !dbg !1123
  store i32 %call22, i32* %retval, align 4, !dbg !1124
  br label %return, !dbg !1124

return:                                           ; preds = %sw.epilog, %sw.bb20, %if.then17, %if.then8, %if.then, %sw.bb
  %28 = load i32, i32* %retval, align 4, !dbg !1125
  ret i32 %28, !dbg !1125
}

; Function Attrs: nounwind uwtable
define internal i32 @attlist5(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !197 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1126, metadata !269), !dbg !1127
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1128, metadata !269), !dbg !1129
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1130, metadata !269), !dbg !1131
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1132, metadata !269), !dbg !1133
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1134, metadata !269), !dbg !1135
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1136
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 23, label %sw.bb1
  ], !dbg !1137

sw.bb:                                            ; preds = %entry
  store i32 33, i32* %retval, align 4, !dbg !1138
  br label %return, !dbg !1138

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1140
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1141
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist6, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1142
  store i32 33, i32* %retval, align 4, !dbg !1143
  br label %return, !dbg !1143

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1144
  %3 = load i32, i32* %tok.addr, align 4, !dbg !1145
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !1146
  store i32 %call, i32* %retval, align 4, !dbg !1147
  br label %return, !dbg !1147

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !1148
  ret i32 %4, !dbg !1148
}

; Function Attrs: nounwind uwtable
define internal i32 @attlist3(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !200 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1149, metadata !269), !dbg !1150
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1151, metadata !269), !dbg !1152
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1153, metadata !269), !dbg !1154
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1155, metadata !269), !dbg !1156
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1157, metadata !269), !dbg !1158
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1159
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 19, label %sw.bb1
    i32 18, label %sw.bb1
    i32 41, label %sw.bb1
  ], !dbg !1160

sw.bb:                                            ; preds = %entry
  store i32 33, i32* %retval, align 4, !dbg !1161
  br label %return, !dbg !1161

sw.bb1:                                           ; preds = %entry, %entry, %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1163
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1164
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist4, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1165
  store i32 31, i32* %retval, align 4, !dbg !1166
  br label %return, !dbg !1166

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1167
  %3 = load i32, i32* %tok.addr, align 4, !dbg !1168
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !1169
  store i32 %call, i32* %retval, align 4, !dbg !1170
  br label %return, !dbg !1170

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !1171
  ret i32 %4, !dbg !1171
}

; Function Attrs: nounwind uwtable
define internal i32 @attlist9(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !196 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1172, metadata !269), !dbg !1173
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1174, metadata !269), !dbg !1175
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1176, metadata !269), !dbg !1177
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1178, metadata !269), !dbg !1179
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1180, metadata !269), !dbg !1181
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1182
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 27, label %sw.bb1
  ], !dbg !1183

sw.bb:                                            ; preds = %entry
  store i32 33, i32* %retval, align 4, !dbg !1184
  br label %return, !dbg !1184

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1186
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1187
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist1, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1188
  store i32 38, i32* %retval, align 4, !dbg !1189
  br label %return, !dbg !1189

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1190
  %3 = load i32, i32* %tok.addr, align 4, !dbg !1191
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !1192
  store i32 %call, i32* %retval, align 4, !dbg !1193
  br label %return, !dbg !1193

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !1194
  ret i32 %4, !dbg !1194
}

; Function Attrs: nounwind uwtable
define internal i32 @attlist6(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !198 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1195, metadata !269), !dbg !1196
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1197, metadata !269), !dbg !1198
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1199, metadata !269), !dbg !1200
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1201, metadata !269), !dbg !1202
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1203, metadata !269), !dbg !1204
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1205
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 18, label %sw.bb1
  ], !dbg !1206

sw.bb:                                            ; preds = %entry
  store i32 33, i32* %retval, align 4, !dbg !1207
  br label %return, !dbg !1207

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1209
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1210
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist7, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1211
  store i32 32, i32* %retval, align 4, !dbg !1212
  br label %return, !dbg !1212

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1213
  %3 = load i32, i32* %tok.addr, align 4, !dbg !1214
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !1215
  store i32 %call, i32* %retval, align 4, !dbg !1216
  br label %return, !dbg !1216

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !1217
  ret i32 %4, !dbg !1217
}

; Function Attrs: nounwind uwtable
define internal i32 @attlist7(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !199 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1218, metadata !269), !dbg !1219
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1220, metadata !269), !dbg !1221
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1222, metadata !269), !dbg !1223
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1224, metadata !269), !dbg !1225
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1226, metadata !269), !dbg !1227
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1228
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 24, label %sw.bb1
    i32 21, label %sw.bb2
  ], !dbg !1229

sw.bb:                                            ; preds = %entry
  store i32 33, i32* %retval, align 4, !dbg !1230
  br label %return, !dbg !1230

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1232
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1233
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist8, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1234
  store i32 33, i32* %retval, align 4, !dbg !1235
  br label %return, !dbg !1235

sw.bb2:                                           ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1236
  %handler3 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %2, i32 0, i32 0, !dbg !1237
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist6, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler3, align 8, !dbg !1238
  store i32 33, i32* %retval, align 4, !dbg !1239
  br label %return, !dbg !1239

sw.epilog:                                        ; preds = %entry
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1240
  %4 = load i32, i32* %tok.addr, align 4, !dbg !1241
  %call = call i32 @common(%struct.prolog_state* %3, i32 %4), !dbg !1242
  store i32 %call, i32* %retval, align 4, !dbg !1243
  br label %return, !dbg !1243

return:                                           ; preds = %sw.epilog, %sw.bb2, %sw.bb1, %sw.bb
  %5 = load i32, i32* %retval, align 4, !dbg !1244
  ret i32 %5, !dbg !1244
}

; Function Attrs: nounwind uwtable
define internal i32 @attlist4(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !201 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1245, metadata !269), !dbg !1246
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1247, metadata !269), !dbg !1248
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1249, metadata !269), !dbg !1250
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1251, metadata !269), !dbg !1252
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1253, metadata !269), !dbg !1254
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1255
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 24, label %sw.bb1
    i32 21, label %sw.bb2
  ], !dbg !1256

sw.bb:                                            ; preds = %entry
  store i32 33, i32* %retval, align 4, !dbg !1257
  br label %return, !dbg !1257

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1259
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1260
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist8, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1261
  store i32 33, i32* %retval, align 4, !dbg !1262
  br label %return, !dbg !1262

sw.bb2:                                           ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1263
  %handler3 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %2, i32 0, i32 0, !dbg !1264
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @attlist3, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler3, align 8, !dbg !1265
  store i32 33, i32* %retval, align 4, !dbg !1266
  br label %return, !dbg !1266

sw.epilog:                                        ; preds = %entry
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1267
  %4 = load i32, i32* %tok.addr, align 4, !dbg !1268
  %call = call i32 @common(%struct.prolog_state* %3, i32 %4), !dbg !1269
  store i32 %call, i32* %retval, align 4, !dbg !1270
  br label %return, !dbg !1270

return:                                           ; preds = %sw.epilog, %sw.bb2, %sw.bb1, %sw.bb
  %5 = load i32, i32* %retval, align 4, !dbg !1271
  ret i32 %5, !dbg !1271
}

; Function Attrs: nounwind uwtable
define internal i32 @element1(%struct.prolog_state* %state, i32 %tok, i8* %ptr, i8* %end, %struct.encoding* %enc) #0 !dbg !203 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %end.addr = alloca i8*, align 8
  %enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1272, metadata !269), !dbg !1273
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1274, metadata !269), !dbg !1275
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !1276, metadata !269), !dbg !1277
  store i8* %end, i8** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %end.addr, metadata !1278, metadata !269), !dbg !1279
  store %struct.encoding* %enc, %struct.encoding** %enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %enc.addr, metadata !1280, metadata !269), !dbg !1281
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1282
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 18, label %sw.bb1
    i32 23, label %sw.bb9
  ], !dbg !1283

sw.bb:                                            ; preds = %entry
  store i32 39, i32* %retval, align 4, !dbg !1284
  br label %return, !dbg !1284

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1286
  %nameMatchesAscii = getelementptr inbounds %struct.encoding, %struct.encoding* %1, i32 0, i32 3, !dbg !1286
  %2 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii, align 8, !dbg !1286
  %3 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1286
  %4 = load i8*, i8** %ptr.addr, align 8, !dbg !1286
  %5 = load i8*, i8** %end.addr, align 8, !dbg !1286
  %call = call i32 %2(%struct.encoding* %3, i8* %4, i8* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @KW_EMPTY, i32 0, i32 0)), !dbg !1286
  %tobool = icmp ne i32 %call, 0, !dbg !1286
  br i1 %tobool, label %if.then, label %if.end, !dbg !1288

if.then:                                          ; preds = %sw.bb1
  %6 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1289
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %6, i32 0, i32 0, !dbg !1291
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1292
  %7 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1293
  %role_none = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %7, i32 0, i32 2, !dbg !1294
  store i32 39, i32* %role_none, align 4, !dbg !1295
  store i32 42, i32* %retval, align 4, !dbg !1296
  br label %return, !dbg !1296

if.end:                                           ; preds = %sw.bb1
  %8 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1297
  %nameMatchesAscii2 = getelementptr inbounds %struct.encoding, %struct.encoding* %8, i32 0, i32 3, !dbg !1297
  %9 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii2, align 8, !dbg !1297
  %10 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1297
  %11 = load i8*, i8** %ptr.addr, align 8, !dbg !1297
  %12 = load i8*, i8** %end.addr, align 8, !dbg !1297
  %call3 = call i32 %9(%struct.encoding* %10, i8* %11, i8* %12, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @KW_ANY, i32 0, i32 0)), !dbg !1297
  %tobool4 = icmp ne i32 %call3, 0, !dbg !1297
  br i1 %tobool4, label %if.then5, label %if.end8, !dbg !1299

if.then5:                                         ; preds = %if.end
  %13 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1300
  %handler6 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %13, i32 0, i32 0, !dbg !1302
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler6, align 8, !dbg !1303
  %14 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1304
  %role_none7 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %14, i32 0, i32 2, !dbg !1305
  store i32 39, i32* %role_none7, align 4, !dbg !1306
  store i32 41, i32* %retval, align 4, !dbg !1307
  br label %return, !dbg !1307

if.end8:                                          ; preds = %if.end
  br label %sw.epilog, !dbg !1308

sw.bb9:                                           ; preds = %entry
  %15 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1309
  %handler10 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %15, i32 0, i32 0, !dbg !1310
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element2, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler10, align 8, !dbg !1311
  %16 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1312
  %level = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %16, i32 0, i32 1, !dbg !1313
  store i32 1, i32* %level, align 8, !dbg !1314
  store i32 44, i32* %retval, align 4, !dbg !1315
  br label %return, !dbg !1315

sw.epilog:                                        ; preds = %entry, %if.end8
  %17 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1316
  %18 = load i32, i32* %tok.addr, align 4, !dbg !1317
  %call11 = call i32 @common(%struct.prolog_state* %17, i32 %18), !dbg !1318
  store i32 %call11, i32* %retval, align 4, !dbg !1319
  br label %return, !dbg !1319

return:                                           ; preds = %sw.epilog, %sw.bb9, %if.then5, %if.then, %sw.bb
  %19 = load i32, i32* %retval, align 4, !dbg !1320
  ret i32 %19, !dbg !1320
}

; Function Attrs: nounwind uwtable
define internal i32 @element2(%struct.prolog_state* %state, i32 %tok, i8* %ptr, i8* %end, %struct.encoding* %enc) #0 !dbg !204 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %end.addr = alloca i8*, align 8
  %enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1321, metadata !269), !dbg !1322
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1323, metadata !269), !dbg !1324
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !1325, metadata !269), !dbg !1326
  store i8* %end, i8** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %end.addr, metadata !1327, metadata !269), !dbg !1328
  store %struct.encoding* %enc, %struct.encoding** %enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %enc.addr, metadata !1329, metadata !269), !dbg !1330
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1331
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 20, label %sw.bb1
    i32 23, label %sw.bb2
    i32 18, label %sw.bb4
    i32 41, label %sw.bb4
    i32 30, label %sw.bb6
    i32 31, label %sw.bb8
    i32 32, label %sw.bb10
  ], !dbg !1332

sw.bb:                                            ; preds = %entry
  store i32 39, i32* %retval, align 4, !dbg !1333
  br label %return, !dbg !1333

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1335
  %nameMatchesAscii = getelementptr inbounds %struct.encoding, %struct.encoding* %1, i32 0, i32 3, !dbg !1335
  %2 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii, align 8, !dbg !1335
  %3 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1335
  %4 = load i8*, i8** %ptr.addr, align 8, !dbg !1335
  %5 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1335
  %minBytesPerChar = getelementptr inbounds %struct.encoding, %struct.encoding* %5, i32 0, i32 13, !dbg !1335
  %6 = load i32, i32* %minBytesPerChar, align 8, !dbg !1335
  %idx.ext = sext i32 %6 to i64, !dbg !1335
  %add.ptr = getelementptr inbounds i8, i8* %4, i64 %idx.ext, !dbg !1335
  %7 = load i8*, i8** %end.addr, align 8, !dbg !1335
  %call = call i32 %2(%struct.encoding* %3, i8* %add.ptr, i8* %7, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @KW_PCDATA, i32 0, i32 0)), !dbg !1335
  %tobool = icmp ne i32 %call, 0, !dbg !1335
  br i1 %tobool, label %if.then, label %if.end, !dbg !1337

if.then:                                          ; preds = %sw.bb1
  %8 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1338
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %8, i32 0, i32 0, !dbg !1340
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element3, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1341
  store i32 43, i32* %retval, align 4, !dbg !1342
  br label %return, !dbg !1342

if.end:                                           ; preds = %sw.bb1
  br label %sw.epilog, !dbg !1343

sw.bb2:                                           ; preds = %entry
  %9 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1344
  %level = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %9, i32 0, i32 1, !dbg !1345
  store i32 2, i32* %level, align 8, !dbg !1346
  %10 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1347
  %handler3 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %10, i32 0, i32 0, !dbg !1348
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element6, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler3, align 8, !dbg !1349
  store i32 44, i32* %retval, align 4, !dbg !1350
  br label %return, !dbg !1350

sw.bb4:                                           ; preds = %entry, %entry
  %11 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1351
  %handler5 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %11, i32 0, i32 0, !dbg !1352
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element7, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler5, align 8, !dbg !1353
  store i32 51, i32* %retval, align 4, !dbg !1354
  br label %return, !dbg !1354

sw.bb6:                                           ; preds = %entry
  %12 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1355
  %handler7 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %12, i32 0, i32 0, !dbg !1356
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element7, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler7, align 8, !dbg !1357
  store i32 53, i32* %retval, align 4, !dbg !1358
  br label %return, !dbg !1358

sw.bb8:                                           ; preds = %entry
  %13 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1359
  %handler9 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %13, i32 0, i32 0, !dbg !1360
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element7, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler9, align 8, !dbg !1361
  store i32 52, i32* %retval, align 4, !dbg !1362
  br label %return, !dbg !1362

sw.bb10:                                          ; preds = %entry
  %14 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1363
  %handler11 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %14, i32 0, i32 0, !dbg !1364
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element7, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler11, align 8, !dbg !1365
  store i32 54, i32* %retval, align 4, !dbg !1366
  br label %return, !dbg !1366

sw.epilog:                                        ; preds = %entry, %if.end
  %15 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1367
  %16 = load i32, i32* %tok.addr, align 4, !dbg !1368
  %call12 = call i32 @common(%struct.prolog_state* %15, i32 %16), !dbg !1369
  store i32 %call12, i32* %retval, align 4, !dbg !1370
  br label %return, !dbg !1370

return:                                           ; preds = %sw.epilog, %sw.bb10, %sw.bb8, %sw.bb6, %sw.bb4, %sw.bb2, %if.then, %sw.bb
  %17 = load i32, i32* %retval, align 4, !dbg !1371
  ret i32 %17, !dbg !1371
}

; Function Attrs: nounwind uwtable
define internal i32 @element3(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !205 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1372, metadata !269), !dbg !1373
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1374, metadata !269), !dbg !1375
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1376, metadata !269), !dbg !1377
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1378, metadata !269), !dbg !1379
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1380, metadata !269), !dbg !1381
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1382
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 24, label %sw.bb1
    i32 36, label %sw.bb2
    i32 21, label %sw.bb5
  ], !dbg !1383

sw.bb:                                            ; preds = %entry
  store i32 39, i32* %retval, align 4, !dbg !1384
  br label %return, !dbg !1384

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1386
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1387
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1388
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1389
  %role_none = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %2, i32 0, i32 2, !dbg !1390
  store i32 39, i32* %role_none, align 4, !dbg !1391
  store i32 45, i32* %retval, align 4, !dbg !1392
  br label %return, !dbg !1392

sw.bb2:                                           ; preds = %entry
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1393
  %handler3 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %3, i32 0, i32 0, !dbg !1394
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler3, align 8, !dbg !1395
  %4 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1396
  %role_none4 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %4, i32 0, i32 2, !dbg !1397
  store i32 39, i32* %role_none4, align 4, !dbg !1398
  store i32 46, i32* %retval, align 4, !dbg !1399
  br label %return, !dbg !1399

sw.bb5:                                           ; preds = %entry
  %5 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1400
  %handler6 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %5, i32 0, i32 0, !dbg !1401
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element4, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler6, align 8, !dbg !1402
  store i32 39, i32* %retval, align 4, !dbg !1403
  br label %return, !dbg !1403

sw.epilog:                                        ; preds = %entry
  %6 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1404
  %7 = load i32, i32* %tok.addr, align 4, !dbg !1405
  %call = call i32 @common(%struct.prolog_state* %6, i32 %7), !dbg !1406
  store i32 %call, i32* %retval, align 4, !dbg !1407
  br label %return, !dbg !1407

return:                                           ; preds = %sw.epilog, %sw.bb5, %sw.bb2, %sw.bb1, %sw.bb
  %8 = load i32, i32* %retval, align 4, !dbg !1408
  ret i32 %8, !dbg !1408
}

; Function Attrs: nounwind uwtable
define internal i32 @element6(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !208 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1409, metadata !269), !dbg !1410
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1411, metadata !269), !dbg !1412
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1413, metadata !269), !dbg !1414
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1415, metadata !269), !dbg !1416
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1417, metadata !269), !dbg !1418
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1419
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 23, label %sw.bb1
    i32 18, label %sw.bb2
    i32 41, label %sw.bb2
    i32 30, label %sw.bb3
    i32 31, label %sw.bb5
    i32 32, label %sw.bb7
  ], !dbg !1420

sw.bb:                                            ; preds = %entry
  store i32 39, i32* %retval, align 4, !dbg !1421
  br label %return, !dbg !1421

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1423
  %level = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 1, !dbg !1424
  %2 = load i32, i32* %level, align 8, !dbg !1425
  %add = add i32 %2, 1, !dbg !1425
  store i32 %add, i32* %level, align 8, !dbg !1425
  store i32 44, i32* %retval, align 4, !dbg !1426
  br label %return, !dbg !1426

sw.bb2:                                           ; preds = %entry, %entry
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1427
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %3, i32 0, i32 0, !dbg !1428
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element7, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1429
  store i32 51, i32* %retval, align 4, !dbg !1430
  br label %return, !dbg !1430

sw.bb3:                                           ; preds = %entry
  %4 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1431
  %handler4 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %4, i32 0, i32 0, !dbg !1432
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element7, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler4, align 8, !dbg !1433
  store i32 53, i32* %retval, align 4, !dbg !1434
  br label %return, !dbg !1434

sw.bb5:                                           ; preds = %entry
  %5 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1435
  %handler6 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %5, i32 0, i32 0, !dbg !1436
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element7, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler6, align 8, !dbg !1437
  store i32 52, i32* %retval, align 4, !dbg !1438
  br label %return, !dbg !1438

sw.bb7:                                           ; preds = %entry
  %6 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1439
  %handler8 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %6, i32 0, i32 0, !dbg !1440
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element7, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler8, align 8, !dbg !1441
  store i32 54, i32* %retval, align 4, !dbg !1442
  br label %return, !dbg !1442

sw.epilog:                                        ; preds = %entry
  %7 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1443
  %8 = load i32, i32* %tok.addr, align 4, !dbg !1444
  %call = call i32 @common(%struct.prolog_state* %7, i32 %8), !dbg !1445
  store i32 %call, i32* %retval, align 4, !dbg !1446
  br label %return, !dbg !1446

return:                                           ; preds = %sw.epilog, %sw.bb7, %sw.bb5, %sw.bb3, %sw.bb2, %sw.bb1, %sw.bb
  %9 = load i32, i32* %retval, align 4, !dbg !1447
  ret i32 %9, !dbg !1447
}

; Function Attrs: nounwind uwtable
define internal i32 @element7(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !209 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1448, metadata !269), !dbg !1449
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1450, metadata !269), !dbg !1451
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1452, metadata !269), !dbg !1453
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1454, metadata !269), !dbg !1455
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1456, metadata !269), !dbg !1457
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1458
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 24, label %sw.bb1
    i32 36, label %sw.bb3
    i32 35, label %sw.bb12
    i32 37, label %sw.bb21
    i32 38, label %sw.bb30
    i32 21, label %sw.bb32
  ], !dbg !1459

sw.bb:                                            ; preds = %entry
  store i32 39, i32* %retval, align 4, !dbg !1460
  br label %return, !dbg !1460

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1462
  %level = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 1, !dbg !1463
  %2 = load i32, i32* %level, align 8, !dbg !1464
  %sub = sub i32 %2, 1, !dbg !1464
  store i32 %sub, i32* %level, align 8, !dbg !1464
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1465
  %level2 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %3, i32 0, i32 1, !dbg !1467
  %4 = load i32, i32* %level2, align 8, !dbg !1467
  %cmp = icmp eq i32 %4, 0, !dbg !1468
  br i1 %cmp, label %if.then, label %if.end, !dbg !1469

if.then:                                          ; preds = %sw.bb1
  %5 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1470
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %5, i32 0, i32 0, !dbg !1472
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1473
  %6 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1474
  %role_none = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %6, i32 0, i32 2, !dbg !1475
  store i32 39, i32* %role_none, align 4, !dbg !1476
  br label %if.end, !dbg !1477

if.end:                                           ; preds = %if.then, %sw.bb1
  store i32 45, i32* %retval, align 4, !dbg !1478
  br label %return, !dbg !1478

sw.bb3:                                           ; preds = %entry
  %7 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1479
  %level4 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %7, i32 0, i32 1, !dbg !1480
  %8 = load i32, i32* %level4, align 8, !dbg !1481
  %sub5 = sub i32 %8, 1, !dbg !1481
  store i32 %sub5, i32* %level4, align 8, !dbg !1481
  %9 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1482
  %level6 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %9, i32 0, i32 1, !dbg !1484
  %10 = load i32, i32* %level6, align 8, !dbg !1484
  %cmp7 = icmp eq i32 %10, 0, !dbg !1485
  br i1 %cmp7, label %if.then8, label %if.end11, !dbg !1486

if.then8:                                         ; preds = %sw.bb3
  %11 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1487
  %handler9 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %11, i32 0, i32 0, !dbg !1489
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler9, align 8, !dbg !1490
  %12 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1491
  %role_none10 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %12, i32 0, i32 2, !dbg !1492
  store i32 39, i32* %role_none10, align 4, !dbg !1493
  br label %if.end11, !dbg !1494

if.end11:                                         ; preds = %if.then8, %sw.bb3
  store i32 46, i32* %retval, align 4, !dbg !1495
  br label %return, !dbg !1495

sw.bb12:                                          ; preds = %entry
  %13 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1496
  %level13 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %13, i32 0, i32 1, !dbg !1497
  %14 = load i32, i32* %level13, align 8, !dbg !1498
  %sub14 = sub i32 %14, 1, !dbg !1498
  store i32 %sub14, i32* %level13, align 8, !dbg !1498
  %15 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1499
  %level15 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %15, i32 0, i32 1, !dbg !1501
  %16 = load i32, i32* %level15, align 8, !dbg !1501
  %cmp16 = icmp eq i32 %16, 0, !dbg !1502
  br i1 %cmp16, label %if.then17, label %if.end20, !dbg !1503

if.then17:                                        ; preds = %sw.bb12
  %17 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1504
  %handler18 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %17, i32 0, i32 0, !dbg !1506
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler18, align 8, !dbg !1507
  %18 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1508
  %role_none19 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %18, i32 0, i32 2, !dbg !1509
  store i32 39, i32* %role_none19, align 4, !dbg !1510
  br label %if.end20, !dbg !1511

if.end20:                                         ; preds = %if.then17, %sw.bb12
  store i32 47, i32* %retval, align 4, !dbg !1512
  br label %return, !dbg !1512

sw.bb21:                                          ; preds = %entry
  %19 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1513
  %level22 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %19, i32 0, i32 1, !dbg !1514
  %20 = load i32, i32* %level22, align 8, !dbg !1515
  %sub23 = sub i32 %20, 1, !dbg !1515
  store i32 %sub23, i32* %level22, align 8, !dbg !1515
  %21 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1516
  %level24 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %21, i32 0, i32 1, !dbg !1518
  %22 = load i32, i32* %level24, align 8, !dbg !1518
  %cmp25 = icmp eq i32 %22, 0, !dbg !1519
  br i1 %cmp25, label %if.then26, label %if.end29, !dbg !1520

if.then26:                                        ; preds = %sw.bb21
  %23 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1521
  %handler27 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %23, i32 0, i32 0, !dbg !1523
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler27, align 8, !dbg !1524
  %24 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1525
  %role_none28 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %24, i32 0, i32 2, !dbg !1526
  store i32 39, i32* %role_none28, align 4, !dbg !1527
  br label %if.end29, !dbg !1528

if.end29:                                         ; preds = %if.then26, %sw.bb21
  store i32 48, i32* %retval, align 4, !dbg !1529
  br label %return, !dbg !1529

sw.bb30:                                          ; preds = %entry
  %25 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1530
  %handler31 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %25, i32 0, i32 0, !dbg !1531
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element6, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler31, align 8, !dbg !1532
  store i32 50, i32* %retval, align 4, !dbg !1533
  br label %return, !dbg !1533

sw.bb32:                                          ; preds = %entry
  %26 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1534
  %handler33 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %26, i32 0, i32 0, !dbg !1535
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element6, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler33, align 8, !dbg !1536
  store i32 49, i32* %retval, align 4, !dbg !1537
  br label %return, !dbg !1537

sw.epilog:                                        ; preds = %entry
  %27 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1538
  %28 = load i32, i32* %tok.addr, align 4, !dbg !1539
  %call = call i32 @common(%struct.prolog_state* %27, i32 %28), !dbg !1540
  store i32 %call, i32* %retval, align 4, !dbg !1541
  br label %return, !dbg !1541

return:                                           ; preds = %sw.epilog, %sw.bb32, %sw.bb30, %if.end29, %if.end20, %if.end11, %if.end, %sw.bb
  %29 = load i32, i32* %retval, align 4, !dbg !1542
  ret i32 %29, !dbg !1542
}

; Function Attrs: nounwind uwtable
define internal i32 @element4(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !206 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1543, metadata !269), !dbg !1544
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1545, metadata !269), !dbg !1546
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1547, metadata !269), !dbg !1548
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1549, metadata !269), !dbg !1550
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1551, metadata !269), !dbg !1552
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1553
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 18, label %sw.bb1
    i32 41, label %sw.bb1
  ], !dbg !1554

sw.bb:                                            ; preds = %entry
  store i32 39, i32* %retval, align 4, !dbg !1555
  br label %return, !dbg !1555

sw.bb1:                                           ; preds = %entry, %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1557
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1558
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element5, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1559
  store i32 51, i32* %retval, align 4, !dbg !1560
  br label %return, !dbg !1560

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1561
  %3 = load i32, i32* %tok.addr, align 4, !dbg !1562
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !1563
  store i32 %call, i32* %retval, align 4, !dbg !1564
  br label %return, !dbg !1564

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !1565
  ret i32 %4, !dbg !1565
}

; Function Attrs: nounwind uwtable
define internal i32 @element5(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !207 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1566, metadata !269), !dbg !1567
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1568, metadata !269), !dbg !1569
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1570, metadata !269), !dbg !1571
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1572, metadata !269), !dbg !1573
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1574, metadata !269), !dbg !1575
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1576
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 36, label %sw.bb1
    i32 21, label %sw.bb2
  ], !dbg !1577

sw.bb:                                            ; preds = %entry
  store i32 39, i32* %retval, align 4, !dbg !1578
  br label %return, !dbg !1578

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1580
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1581
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1582
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1583
  %role_none = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %2, i32 0, i32 2, !dbg !1584
  store i32 39, i32* %role_none, align 4, !dbg !1585
  store i32 46, i32* %retval, align 4, !dbg !1586
  br label %return, !dbg !1586

sw.bb2:                                           ; preds = %entry
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1587
  %handler3 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %3, i32 0, i32 0, !dbg !1588
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @element4, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler3, align 8, !dbg !1589
  store i32 39, i32* %retval, align 4, !dbg !1590
  br label %return, !dbg !1590

sw.epilog:                                        ; preds = %entry
  %4 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1591
  %5 = load i32, i32* %tok.addr, align 4, !dbg !1592
  %call = call i32 @common(%struct.prolog_state* %4, i32 %5), !dbg !1593
  store i32 %call, i32* %retval, align 4, !dbg !1594
  br label %return, !dbg !1594

return:                                           ; preds = %sw.epilog, %sw.bb2, %sw.bb1, %sw.bb
  %6 = load i32, i32* %retval, align 4, !dbg !1595
  ret i32 %6, !dbg !1595
}

; Function Attrs: nounwind uwtable
define internal i32 @notation1(%struct.prolog_state* %state, i32 %tok, i8* %ptr, i8* %end, %struct.encoding* %enc) #0 !dbg !211 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %end.addr = alloca i8*, align 8
  %enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1596, metadata !269), !dbg !1597
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1598, metadata !269), !dbg !1599
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !1600, metadata !269), !dbg !1601
  store i8* %end, i8** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %end.addr, metadata !1602, metadata !269), !dbg !1603
  store %struct.encoding* %enc, %struct.encoding** %enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %enc.addr, metadata !1604, metadata !269), !dbg !1605
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1606
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 18, label %sw.bb1
  ], !dbg !1607

sw.bb:                                            ; preds = %entry
  store i32 17, i32* %retval, align 4, !dbg !1608
  br label %return, !dbg !1608

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1610
  %nameMatchesAscii = getelementptr inbounds %struct.encoding, %struct.encoding* %1, i32 0, i32 3, !dbg !1610
  %2 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii, align 8, !dbg !1610
  %3 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1610
  %4 = load i8*, i8** %ptr.addr, align 8, !dbg !1610
  %5 = load i8*, i8** %end.addr, align 8, !dbg !1610
  %call = call i32 %2(%struct.encoding* %3, i8* %4, i8* %5, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @KW_SYSTEM, i32 0, i32 0)), !dbg !1610
  %tobool = icmp ne i32 %call, 0, !dbg !1610
  br i1 %tobool, label %if.then, label %if.end, !dbg !1612

if.then:                                          ; preds = %sw.bb1
  %6 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1613
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %6, i32 0, i32 0, !dbg !1615
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @notation3, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1616
  store i32 17, i32* %retval, align 4, !dbg !1617
  br label %return, !dbg !1617

if.end:                                           ; preds = %sw.bb1
  %7 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1618
  %nameMatchesAscii2 = getelementptr inbounds %struct.encoding, %struct.encoding* %7, i32 0, i32 3, !dbg !1618
  %8 = load i32 (%struct.encoding*, i8*, i8*, i8*)*, i32 (%struct.encoding*, i8*, i8*, i8*)** %nameMatchesAscii2, align 8, !dbg !1618
  %9 = load %struct.encoding*, %struct.encoding** %enc.addr, align 8, !dbg !1618
  %10 = load i8*, i8** %ptr.addr, align 8, !dbg !1618
  %11 = load i8*, i8** %end.addr, align 8, !dbg !1618
  %call3 = call i32 %8(%struct.encoding* %9, i8* %10, i8* %11, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @KW_PUBLIC, i32 0, i32 0)), !dbg !1618
  %tobool4 = icmp ne i32 %call3, 0, !dbg !1618
  br i1 %tobool4, label %if.then5, label %if.end7, !dbg !1620

if.then5:                                         ; preds = %if.end
  %12 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1621
  %handler6 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %12, i32 0, i32 0, !dbg !1623
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @notation2, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler6, align 8, !dbg !1624
  store i32 17, i32* %retval, align 4, !dbg !1625
  br label %return, !dbg !1625

if.end7:                                          ; preds = %if.end
  br label %sw.epilog, !dbg !1626

sw.epilog:                                        ; preds = %entry, %if.end7
  %13 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1627
  %14 = load i32, i32* %tok.addr, align 4, !dbg !1628
  %call8 = call i32 @common(%struct.prolog_state* %13, i32 %14), !dbg !1629
  store i32 %call8, i32* %retval, align 4, !dbg !1630
  br label %return, !dbg !1630

return:                                           ; preds = %sw.epilog, %if.then5, %if.then, %sw.bb
  %15 = load i32, i32* %retval, align 4, !dbg !1631
  ret i32 %15, !dbg !1631
}

; Function Attrs: nounwind uwtable
define internal i32 @notation3(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !212 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1632, metadata !269), !dbg !1633
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1634, metadata !269), !dbg !1635
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1636, metadata !269), !dbg !1637
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1638, metadata !269), !dbg !1639
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1640, metadata !269), !dbg !1641
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1642
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 27, label %sw.bb1
  ], !dbg !1643

sw.bb:                                            ; preds = %entry
  store i32 17, i32* %retval, align 4, !dbg !1644
  br label %return, !dbg !1644

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1646
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1647
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1648
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1649
  %role_none = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %2, i32 0, i32 2, !dbg !1650
  store i32 17, i32* %role_none, align 4, !dbg !1651
  store i32 19, i32* %retval, align 4, !dbg !1652
  br label %return, !dbg !1652

sw.epilog:                                        ; preds = %entry
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1653
  %4 = load i32, i32* %tok.addr, align 4, !dbg !1654
  %call = call i32 @common(%struct.prolog_state* %3, i32 %4), !dbg !1655
  store i32 %call, i32* %retval, align 4, !dbg !1656
  br label %return, !dbg !1656

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %5 = load i32, i32* %retval, align 4, !dbg !1657
  ret i32 %5, !dbg !1657
}

; Function Attrs: nounwind uwtable
define internal i32 @notation2(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !213 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1658, metadata !269), !dbg !1659
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1660, metadata !269), !dbg !1661
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1662, metadata !269), !dbg !1663
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1664, metadata !269), !dbg !1665
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1666, metadata !269), !dbg !1667
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1668
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 27, label %sw.bb1
  ], !dbg !1669

sw.bb:                                            ; preds = %entry
  store i32 17, i32* %retval, align 4, !dbg !1670
  br label %return, !dbg !1670

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1672
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1673
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @notation4, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1674
  store i32 21, i32* %retval, align 4, !dbg !1675
  br label %return, !dbg !1675

sw.epilog:                                        ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1676
  %3 = load i32, i32* %tok.addr, align 4, !dbg !1677
  %call = call i32 @common(%struct.prolog_state* %2, i32 %3), !dbg !1678
  store i32 %call, i32* %retval, align 4, !dbg !1679
  br label %return, !dbg !1679

return:                                           ; preds = %sw.epilog, %sw.bb1, %sw.bb
  %4 = load i32, i32* %retval, align 4, !dbg !1680
  ret i32 %4, !dbg !1680
}

; Function Attrs: nounwind uwtable
define internal i32 @notation4(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !214 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1681, metadata !269), !dbg !1682
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1683, metadata !269), !dbg !1684
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1685, metadata !269), !dbg !1686
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1687, metadata !269), !dbg !1688
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1689, metadata !269), !dbg !1690
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1691
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 27, label %sw.bb1
    i32 17, label %sw.bb2
  ], !dbg !1692

sw.bb:                                            ; preds = %entry
  store i32 17, i32* %retval, align 4, !dbg !1693
  br label %return, !dbg !1693

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1695
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1696
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @declClose, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1697
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1698
  %role_none = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %2, i32 0, i32 2, !dbg !1699
  store i32 17, i32* %role_none, align 4, !dbg !1700
  store i32 19, i32* %retval, align 4, !dbg !1701
  br label %return, !dbg !1701

sw.bb2:                                           ; preds = %entry
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1702
  %handler3 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %3, i32 0, i32 0, !dbg !1702
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @internalSubset, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler3, align 8, !dbg !1702
  store i32 20, i32* %retval, align 4, !dbg !1703
  br label %return, !dbg !1703

sw.epilog:                                        ; preds = %entry
  %4 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1704
  %5 = load i32, i32* %tok.addr, align 4, !dbg !1705
  %call = call i32 @common(%struct.prolog_state* %4, i32 %5), !dbg !1706
  store i32 %call, i32* %retval, align 4, !dbg !1707
  br label %return, !dbg !1707

return:                                           ; preds = %sw.epilog, %sw.bb2, %sw.bb1, %sw.bb
  %6 = load i32, i32* %retval, align 4, !dbg !1708
  ret i32 %6, !dbg !1708
}

; Function Attrs: nounwind uwtable
define internal i32 @doctype4(%struct.prolog_state* %state, i32 %tok, i8* %UNUSED_ptr, i8* %UNUSED_end, %struct.encoding* %UNUSED_enc) #0 !dbg !218 {
entry:
  %retval = alloca i32, align 4
  %state.addr = alloca %struct.prolog_state*, align 8
  %tok.addr = alloca i32, align 4
  %UNUSED_ptr.addr = alloca i8*, align 8
  %UNUSED_end.addr = alloca i8*, align 8
  %UNUSED_enc.addr = alloca %struct.encoding*, align 8
  store %struct.prolog_state* %state, %struct.prolog_state** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.prolog_state** %state.addr, metadata !1709, metadata !269), !dbg !1710
  store i32 %tok, i32* %tok.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tok.addr, metadata !1711, metadata !269), !dbg !1712
  store i8* %UNUSED_ptr, i8** %UNUSED_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_ptr.addr, metadata !1713, metadata !269), !dbg !1714
  store i8* %UNUSED_end, i8** %UNUSED_end.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %UNUSED_end.addr, metadata !1715, metadata !269), !dbg !1716
  store %struct.encoding* %UNUSED_enc, %struct.encoding** %UNUSED_enc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.encoding** %UNUSED_enc.addr, metadata !1717, metadata !269), !dbg !1718
  %0 = load i32, i32* %tok.addr, align 4, !dbg !1719
  switch i32 %0, label %sw.epilog [
    i32 15, label %sw.bb
    i32 25, label %sw.bb1
    i32 17, label %sw.bb2
  ], !dbg !1720

sw.bb:                                            ; preds = %entry
  store i32 3, i32* %retval, align 4, !dbg !1721
  br label %return, !dbg !1721

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1723
  %handler = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %1, i32 0, i32 0, !dbg !1724
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @internalSubset, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler, align 8, !dbg !1725
  store i32 7, i32* %retval, align 4, !dbg !1726
  br label %return, !dbg !1726

sw.bb2:                                           ; preds = %entry
  %2 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1727
  %handler3 = getelementptr inbounds %struct.prolog_state, %struct.prolog_state* %2, i32 0, i32 0, !dbg !1728
  store i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)* @prolog2, i32 (%struct.prolog_state*, i32, i8*, i8*, %struct.encoding*)** %handler3, align 8, !dbg !1729
  store i32 8, i32* %retval, align 4, !dbg !1730
  br label %return, !dbg !1730

sw.epilog:                                        ; preds = %entry
  %3 = load %struct.prolog_state*, %struct.prolog_state** %state.addr, align 8, !dbg !1731
  %4 = load i32, i32* %tok.addr, align 4, !dbg !1732
  %call = call i32 @common(%struct.prolog_state* %3, i32 %4), !dbg !1733
  store i32 %call, i32* %retval, align 4, !dbg !1734
  br label %return, !dbg !1734

return:                                           ; preds = %sw.epilog, %sw.bb2, %sw.bb1, %sw.bb
  %5 = load i32, i32* %retval, align 4, !dbg !1735
  ret i32 %5, !dbg !1735
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!265, !266}
!llvm.ident = !{!267}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !71, subprograms: !73, globals: !224)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmexpat/lib/xmlrole.c", directory: "/data/download/cmake/cmake-master/Utilities/cmexpat")
!2 = !{!3, !9}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "XML_Convert_Result", file: !4, line: 133, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmexpat/lib/xmltok.h", directory: "/data/download/cmake/cmake-master/Utilities/cmexpat")
!5 = !{!6, !7, !8}
!6 = !DIEnumerator(name: "XML_CONVERT_COMPLETED", value: 0)
!7 = !DIEnumerator(name: "XML_CONVERT_INPUT_INCOMPLETE", value: 1)
!8 = !DIEnumerator(name: "XML_CONVERT_OUTPUT_EXHAUSTED", value: 2)
!9 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !10, line: 20, size: 32, align: 32, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmexpat/lib/xmlrole.h", directory: "/data/download/cmake/cmake-master/Utilities/cmexpat")
!11 = !{!12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70}
!12 = !DIEnumerator(name: "XML_ROLE_ERROR", value: -1)
!13 = !DIEnumerator(name: "XML_ROLE_NONE", value: 0)
!14 = !DIEnumerator(name: "XML_ROLE_XML_DECL", value: 1)
!15 = !DIEnumerator(name: "XML_ROLE_INSTANCE_START", value: 2)
!16 = !DIEnumerator(name: "XML_ROLE_DOCTYPE_NONE", value: 3)
!17 = !DIEnumerator(name: "XML_ROLE_DOCTYPE_NAME", value: 4)
!18 = !DIEnumerator(name: "XML_ROLE_DOCTYPE_SYSTEM_ID", value: 5)
!19 = !DIEnumerator(name: "XML_ROLE_DOCTYPE_PUBLIC_ID", value: 6)
!20 = !DIEnumerator(name: "XML_ROLE_DOCTYPE_INTERNAL_SUBSET", value: 7)
!21 = !DIEnumerator(name: "XML_ROLE_DOCTYPE_CLOSE", value: 8)
!22 = !DIEnumerator(name: "XML_ROLE_GENERAL_ENTITY_NAME", value: 9)
!23 = !DIEnumerator(name: "XML_ROLE_PARAM_ENTITY_NAME", value: 10)
!24 = !DIEnumerator(name: "XML_ROLE_ENTITY_NONE", value: 11)
!25 = !DIEnumerator(name: "XML_ROLE_ENTITY_VALUE", value: 12)
!26 = !DIEnumerator(name: "XML_ROLE_ENTITY_SYSTEM_ID", value: 13)
!27 = !DIEnumerator(name: "XML_ROLE_ENTITY_PUBLIC_ID", value: 14)
!28 = !DIEnumerator(name: "XML_ROLE_ENTITY_COMPLETE", value: 15)
!29 = !DIEnumerator(name: "XML_ROLE_ENTITY_NOTATION_NAME", value: 16)
!30 = !DIEnumerator(name: "XML_ROLE_NOTATION_NONE", value: 17)
!31 = !DIEnumerator(name: "XML_ROLE_NOTATION_NAME", value: 18)
!32 = !DIEnumerator(name: "XML_ROLE_NOTATION_SYSTEM_ID", value: 19)
!33 = !DIEnumerator(name: "XML_ROLE_NOTATION_NO_SYSTEM_ID", value: 20)
!34 = !DIEnumerator(name: "XML_ROLE_NOTATION_PUBLIC_ID", value: 21)
!35 = !DIEnumerator(name: "XML_ROLE_ATTRIBUTE_NAME", value: 22)
!36 = !DIEnumerator(name: "XML_ROLE_ATTRIBUTE_TYPE_CDATA", value: 23)
!37 = !DIEnumerator(name: "XML_ROLE_ATTRIBUTE_TYPE_ID", value: 24)
!38 = !DIEnumerator(name: "XML_ROLE_ATTRIBUTE_TYPE_IDREF", value: 25)
!39 = !DIEnumerator(name: "XML_ROLE_ATTRIBUTE_TYPE_IDREFS", value: 26)
!40 = !DIEnumerator(name: "XML_ROLE_ATTRIBUTE_TYPE_ENTITY", value: 27)
!41 = !DIEnumerator(name: "XML_ROLE_ATTRIBUTE_TYPE_ENTITIES", value: 28)
!42 = !DIEnumerator(name: "XML_ROLE_ATTRIBUTE_TYPE_NMTOKEN", value: 29)
!43 = !DIEnumerator(name: "XML_ROLE_ATTRIBUTE_TYPE_NMTOKENS", value: 30)
!44 = !DIEnumerator(name: "XML_ROLE_ATTRIBUTE_ENUM_VALUE", value: 31)
!45 = !DIEnumerator(name: "XML_ROLE_ATTRIBUTE_NOTATION_VALUE", value: 32)
!46 = !DIEnumerator(name: "XML_ROLE_ATTLIST_NONE", value: 33)
!47 = !DIEnumerator(name: "XML_ROLE_ATTLIST_ELEMENT_NAME", value: 34)
!48 = !DIEnumerator(name: "XML_ROLE_IMPLIED_ATTRIBUTE_VALUE", value: 35)
!49 = !DIEnumerator(name: "XML_ROLE_REQUIRED_ATTRIBUTE_VALUE", value: 36)
!50 = !DIEnumerator(name: "XML_ROLE_DEFAULT_ATTRIBUTE_VALUE", value: 37)
!51 = !DIEnumerator(name: "XML_ROLE_FIXED_ATTRIBUTE_VALUE", value: 38)
!52 = !DIEnumerator(name: "XML_ROLE_ELEMENT_NONE", value: 39)
!53 = !DIEnumerator(name: "XML_ROLE_ELEMENT_NAME", value: 40)
!54 = !DIEnumerator(name: "XML_ROLE_CONTENT_ANY", value: 41)
!55 = !DIEnumerator(name: "XML_ROLE_CONTENT_EMPTY", value: 42)
!56 = !DIEnumerator(name: "XML_ROLE_CONTENT_PCDATA", value: 43)
!57 = !DIEnumerator(name: "XML_ROLE_GROUP_OPEN", value: 44)
!58 = !DIEnumerator(name: "XML_ROLE_GROUP_CLOSE", value: 45)
!59 = !DIEnumerator(name: "XML_ROLE_GROUP_CLOSE_REP", value: 46)
!60 = !DIEnumerator(name: "XML_ROLE_GROUP_CLOSE_OPT", value: 47)
!61 = !DIEnumerator(name: "XML_ROLE_GROUP_CLOSE_PLUS", value: 48)
!62 = !DIEnumerator(name: "XML_ROLE_GROUP_CHOICE", value: 49)
!63 = !DIEnumerator(name: "XML_ROLE_GROUP_SEQUENCE", value: 50)
!64 = !DIEnumerator(name: "XML_ROLE_CONTENT_ELEMENT", value: 51)
!65 = !DIEnumerator(name: "XML_ROLE_CONTENT_ELEMENT_REP", value: 52)
!66 = !DIEnumerator(name: "XML_ROLE_CONTENT_ELEMENT_OPT", value: 53)
!67 = !DIEnumerator(name: "XML_ROLE_CONTENT_ELEMENT_PLUS", value: 54)
!68 = !DIEnumerator(name: "XML_ROLE_PI", value: 55)
!69 = !DIEnumerator(name: "XML_ROLE_COMMENT", value: 56)
!70 = !DIEnumerator(name: "XML_ROLE_PARAM_ENTITY_REF", value: 57)
!71 = !{!72}
!72 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!73 = !{!74, !173, !176, !177, !178, !179, !180, !181, !182, !183, !184, !185, !186, !187, !188, !189, !190, !191, !192, !193, !194, !195, !196, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210, !211, !212, !213, !214, !215, !216, !217, !218, !219, !220, !221}
!74 = distinct !DISubprogram(name: "XmlPrologStateInit", scope: !1, file: !1, line: 1316, type: !75, isLocal: false, isDefinition: true, scopeLine: 1317, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!75 = !DISubroutineType(types: !76)
!76 = !{null, !77}
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "PROLOG_STATE", file: !10, line: 100, baseType: !79)
!79 = !DICompositeType(tag: DW_TAG_structure_type, name: "prolog_state", file: !10, line: 87, size: 128, align: 64, elements: !80)
!80 = !{!81, !169, !171}
!81 = !DIDerivedType(tag: DW_TAG_member, name: "handler", scope: !79, file: !10, line: 88, baseType: !82, size: 64, align: 64)
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!83 = !DISubroutineType(types: !84)
!84 = !{!72, !85, !72, !86, !86, !89}
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!87 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !88)
!88 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !91)
!91 = !DIDerivedType(tag: DW_TAG_typedef, name: "ENCODING", file: !4, line: 126, baseType: !92)
!92 = !DICompositeType(tag: DW_TAG_structure_type, name: "encoding", file: !4, line: 139, size: 1088, align: 64, elements: !93)
!93 = !{!94, !103, !107, !111, !115, !119, !123, !135, !136, !137, !150, !151, !157, !166, !167, !168}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "scanners", scope: !92, file: !4, line: 140, baseType: !95, size: 192, align: 64)
!95 = !DICompositeType(tag: DW_TAG_array_type, baseType: !96, size: 192, align: 64, elements: !101)
!96 = !DIDerivedType(tag: DW_TAG_typedef, name: "SCANNER", file: !4, line: 128, baseType: !97)
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !98, size: 64, align: 64)
!98 = !DISubroutineType(types: !99)
!99 = !{!72, !89, !86, !86, !100}
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!101 = !{!102}
!102 = !DISubrange(count: 3)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "literalScanners", scope: !92, file: !4, line: 141, baseType: !104, size: 128, align: 64, offset: 192)
!104 = !DICompositeType(tag: DW_TAG_array_type, baseType: !96, size: 128, align: 64, elements: !105)
!105 = !{!106}
!106 = !DISubrange(count: 2)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "sameName", scope: !92, file: !4, line: 142, baseType: !108, size: 64, align: 64, offset: 320)
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64, align: 64)
!109 = !DISubroutineType(types: !110)
!110 = !{!72, !89, !86, !86}
!111 = !DIDerivedType(tag: DW_TAG_member, name: "nameMatchesAscii", scope: !92, file: !4, line: 145, baseType: !112, size: 64, align: 64, offset: 384)
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !113, size: 64, align: 64)
!113 = !DISubroutineType(types: !114)
!114 = !{!72, !89, !86, !86, !86}
!115 = !DIDerivedType(tag: DW_TAG_member, name: "nameLength", scope: !92, file: !4, line: 149, baseType: !116, size: 64, align: 64, offset: 448)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DISubroutineType(types: !118)
!118 = !{!72, !89, !86}
!119 = !DIDerivedType(tag: DW_TAG_member, name: "skipS", scope: !92, file: !4, line: 150, baseType: !120, size: 64, align: 64, offset: 512)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DISubroutineType(types: !122)
!122 = !{!86, !89, !86}
!123 = !DIDerivedType(tag: DW_TAG_member, name: "getAtts", scope: !92, file: !4, line: 151, baseType: !124, size: 64, align: 64, offset: 576)
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !125, size: 64, align: 64)
!125 = !DISubroutineType(types: !126)
!126 = !{!72, !89, !86, !72, !127}
!127 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !128, size: 64, align: 64)
!128 = !DIDerivedType(tag: DW_TAG_typedef, name: "ATTRIBUTE", file: !4, line: 123, baseType: !129)
!129 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 118, size: 256, align: 64, elements: !130)
!130 = !{!131, !132, !133, !134}
!131 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !129, file: !4, line: 119, baseType: !86, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "valuePtr", scope: !129, file: !4, line: 120, baseType: !86, size: 64, align: 64, offset: 64)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "valueEnd", scope: !129, file: !4, line: 121, baseType: !86, size: 64, align: 64, offset: 128)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "normalized", scope: !129, file: !4, line: 122, baseType: !88, size: 8, align: 8, offset: 192)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "charRefNumber", scope: !92, file: !4, line: 155, baseType: !116, size: 64, align: 64, offset: 640)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "predefinedEntityName", scope: !92, file: !4, line: 156, baseType: !108, size: 64, align: 64, offset: 704)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "updatePosition", scope: !92, file: !4, line: 159, baseType: !138, size: 64, align: 64, offset: 768)
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !139, size: 64, align: 64)
!139 = !DISubroutineType(types: !140)
!140 = !{null, !89, !86, !86, !141}
!141 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !142, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_typedef, name: "POSITION", file: !4, line: 116, baseType: !143)
!143 = !DICompositeType(tag: DW_TAG_structure_type, name: "position", file: !4, line: 112, size: 128, align: 64, elements: !144)
!144 = !{!145, !149}
!145 = !DIDerivedType(tag: DW_TAG_member, name: "lineNumber", scope: !143, file: !4, line: 114, baseType: !146, size: 64, align: 64)
!146 = !DIDerivedType(tag: DW_TAG_typedef, name: "XML_Size", file: !147, line: 124, baseType: !148)
!147 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmexpat/lib/expat_external.h", directory: "/data/download/cmake/cmake-master/Utilities/cmexpat")
!148 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "columnNumber", scope: !143, file: !4, line: 115, baseType: !146, size: 64, align: 64, offset: 64)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "isPublicId", scope: !92, file: !4, line: 163, baseType: !97, size: 64, align: 64, offset: 832)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "utf8Convert", scope: !92, file: !4, line: 167, baseType: !152, size: 64, align: 64, offset: 896)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DISubroutineType(types: !154)
!154 = !{!3, !89, !100, !86, !155, !86}
!155 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !156, size: 64, align: 64)
!156 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !88, size: 64, align: 64)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "utf16Convert", scope: !92, file: !4, line: 172, baseType: !158, size: 64, align: 64, offset: 960)
!158 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !159, size: 64, align: 64)
!159 = !DISubroutineType(types: !160)
!160 = !{!3, !89, !100, !86, !161, !164}
!161 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !162, size: 64, align: 64)
!162 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !163, size: 64, align: 64)
!163 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!164 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !165, size: 64, align: 64)
!165 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !163)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "minBytesPerChar", scope: !92, file: !4, line: 177, baseType: !72, size: 32, align: 32, offset: 1024)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "isUtf8", scope: !92, file: !4, line: 178, baseType: !88, size: 8, align: 8, offset: 1056)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "isUtf16", scope: !92, file: !4, line: 179, baseType: !88, size: 8, align: 8, offset: 1064)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "level", scope: !79, file: !10, line: 93, baseType: !170, size: 32, align: 32, offset: 64)
!170 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "role_none", scope: !79, file: !10, line: 94, baseType: !72, size: 32, align: 32, offset: 96)
!172 = !{}
!173 = distinct !DISubprogram(name: "prolog0", scope: !1, file: !1, line: 128, type: !174, isLocal: true, isDefinition: true, scopeLine: 133, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!174 = !DISubroutineType(types: !175)
!175 = !{!72, !77, !72, !86, !86, !89}
!176 = distinct !DISubprogram(name: "prolog1", scope: !1, file: !1, line: 165, type: !174, isLocal: true, isDefinition: true, scopeLine: 170, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!177 = distinct !DISubprogram(name: "doctype0", scope: !1, file: !1, line: 217, type: !174, isLocal: true, isDefinition: true, scopeLine: 222, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!178 = distinct !DISubprogram(name: "doctype1", scope: !1, file: !1, line: 235, type: !174, isLocal: true, isDefinition: true, scopeLine: 240, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!179 = distinct !DISubprogram(name: "internalSubset", scope: !1, file: !1, line: 336, type: !174, isLocal: true, isDefinition: true, scopeLine: 341, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!180 = distinct !DISubprogram(name: "entity0", scope: !1, file: !1, line: 438, type: !174, isLocal: true, isDefinition: true, scopeLine: 443, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!181 = distinct !DISubprogram(name: "entity1", scope: !1, file: !1, line: 458, type: !174, isLocal: true, isDefinition: true, scopeLine: 463, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!182 = distinct !DISubprogram(name: "entity7", scope: !1, file: !1, line: 578, type: !174, isLocal: true, isDefinition: true, scopeLine: 583, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!183 = distinct !DISubprogram(name: "entity9", scope: !1, file: !1, line: 623, type: !174, isLocal: true, isDefinition: true, scopeLine: 628, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!184 = distinct !DISubprogram(name: "entity10", scope: !1, file: !1, line: 640, type: !174, isLocal: true, isDefinition: true, scopeLine: 645, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!185 = distinct !DISubprogram(name: "entity8", scope: !1, file: !1, line: 606, type: !174, isLocal: true, isDefinition: true, scopeLine: 611, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!186 = distinct !DISubprogram(name: "declClose", scope: !1, file: !1, line: 1278, type: !174, isLocal: true, isDefinition: true, scopeLine: 1283, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!187 = distinct !DISubprogram(name: "entity2", scope: !1, file: !1, line: 475, type: !174, isLocal: true, isDefinition: true, scopeLine: 480, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!188 = distinct !DISubprogram(name: "entity4", scope: !1, file: !1, line: 520, type: !174, isLocal: true, isDefinition: true, scopeLine: 525, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!189 = distinct !DISubprogram(name: "entity5", scope: !1, file: !1, line: 537, type: !174, isLocal: true, isDefinition: true, scopeLine: 542, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!190 = distinct !DISubprogram(name: "entity6", scope: !1, file: !1, line: 560, type: !174, isLocal: true, isDefinition: true, scopeLine: 565, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!191 = distinct !DISubprogram(name: "entity3", scope: !1, file: !1, line: 503, type: !174, isLocal: true, isDefinition: true, scopeLine: 508, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!192 = distinct !DISubprogram(name: "attlist0", scope: !1, file: !1, line: 754, type: !174, isLocal: true, isDefinition: true, scopeLine: 759, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!193 = distinct !DISubprogram(name: "attlist1", scope: !1, file: !1, line: 772, type: !174, isLocal: true, isDefinition: true, scopeLine: 777, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!194 = distinct !DISubprogram(name: "attlist2", scope: !1, file: !1, line: 793, type: !174, isLocal: true, isDefinition: true, scopeLine: 798, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!195 = distinct !DISubprogram(name: "attlist8", scope: !1, file: !1, line: 928, type: !174, isLocal: true, isDefinition: true, scopeLine: 933, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!196 = distinct !DISubprogram(name: "attlist9", scope: !1, file: !1, line: 968, type: !174, isLocal: true, isDefinition: true, scopeLine: 973, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!197 = distinct !DISubprogram(name: "attlist5", scope: !1, file: !1, line: 873, type: !174, isLocal: true, isDefinition: true, scopeLine: 878, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!198 = distinct !DISubprogram(name: "attlist6", scope: !1, file: !1, line: 890, type: !174, isLocal: true, isDefinition: true, scopeLine: 895, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!199 = distinct !DISubprogram(name: "attlist7", scope: !1, file: !1, line: 907, type: !174, isLocal: true, isDefinition: true, scopeLine: 912, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!200 = distinct !DISubprogram(name: "attlist3", scope: !1, file: !1, line: 834, type: !174, isLocal: true, isDefinition: true, scopeLine: 839, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!201 = distinct !DISubprogram(name: "attlist4", scope: !1, file: !1, line: 853, type: !174, isLocal: true, isDefinition: true, scopeLine: 858, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!202 = distinct !DISubprogram(name: "element0", scope: !1, file: !1, line: 985, type: !174, isLocal: true, isDefinition: true, scopeLine: 990, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!203 = distinct !DISubprogram(name: "element1", scope: !1, file: !1, line: 1003, type: !174, isLocal: true, isDefinition: true, scopeLine: 1008, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!204 = distinct !DISubprogram(name: "element2", scope: !1, file: !1, line: 1033, type: !174, isLocal: true, isDefinition: true, scopeLine: 1038, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!205 = distinct !DISubprogram(name: "element3", scope: !1, file: !1, line: 1073, type: !174, isLocal: true, isDefinition: true, scopeLine: 1078, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!206 = distinct !DISubprogram(name: "element4", scope: !1, file: !1, line: 1098, type: !174, isLocal: true, isDefinition: true, scopeLine: 1103, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!207 = distinct !DISubprogram(name: "element5", scope: !1, file: !1, line: 1116, type: !174, isLocal: true, isDefinition: true, scopeLine: 1121, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!208 = distinct !DISubprogram(name: "element6", scope: !1, file: !1, line: 1137, type: !174, isLocal: true, isDefinition: true, scopeLine: 1142, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!209 = distinct !DISubprogram(name: "element7", scope: !1, file: !1, line: 1167, type: !174, isLocal: true, isDefinition: true, scopeLine: 1172, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!210 = distinct !DISubprogram(name: "notation0", scope: !1, file: !1, line: 657, type: !174, isLocal: true, isDefinition: true, scopeLine: 662, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!211 = distinct !DISubprogram(name: "notation1", scope: !1, file: !1, line: 674, type: !174, isLocal: true, isDefinition: true, scopeLine: 679, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!212 = distinct !DISubprogram(name: "notation3", scope: !1, file: !1, line: 715, type: !174, isLocal: true, isDefinition: true, scopeLine: 720, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!213 = distinct !DISubprogram(name: "notation2", scope: !1, file: !1, line: 698, type: !174, isLocal: true, isDefinition: true, scopeLine: 703, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!214 = distinct !DISubprogram(name: "notation4", scope: !1, file: !1, line: 733, type: !174, isLocal: true, isDefinition: true, scopeLine: 738, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!215 = distinct !DISubprogram(name: "doctype5", scope: !1, file: !1, line: 319, type: !174, isLocal: true, isDefinition: true, scopeLine: 324, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!216 = distinct !DISubprogram(name: "prolog2", scope: !1, file: !1, line: 196, type: !174, isLocal: true, isDefinition: true, scopeLine: 201, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!217 = distinct !DISubprogram(name: "doctype3", scope: !1, file: !1, line: 282, type: !174, isLocal: true, isDefinition: true, scopeLine: 287, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!218 = distinct !DISubprogram(name: "doctype4", scope: !1, file: !1, line: 299, type: !174, isLocal: true, isDefinition: true, scopeLine: 304, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!219 = distinct !DISubprogram(name: "doctype2", scope: !1, file: !1, line: 265, type: !174, isLocal: true, isDefinition: true, scopeLine: 270, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!220 = distinct !DISubprogram(name: "error", scope: !1, file: !1, line: 1295, type: !174, isLocal: true, isDefinition: true, scopeLine: 1300, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!221 = distinct !DISubprogram(name: "common", scope: !1, file: !1, line: 1305, type: !222, isLocal: true, isDefinition: true, scopeLine: 1306, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!222 = !DISubroutineType(types: !223)
!223 = !{!72, !77, !72}
!224 = !{!225, !229, !233, !237, !238, !241, !242, !244, !245, !246, !250, !251, !252, !253, !254, !255, !256, !257, !261, !262, !263, !264}
!225 = !DIGlobalVariable(name: "KW_DOCTYPE", scope: !0, file: !1, line: 39, type: !226, isLocal: true, isDefinition: true, variable: [8 x i8]* @KW_DOCTYPE)
!226 = !DICompositeType(tag: DW_TAG_array_type, baseType: !87, size: 64, align: 8, elements: !227)
!227 = !{!228}
!228 = !DISubrange(count: 8)
!229 = !DIGlobalVariable(name: "KW_ENTITY", scope: !0, file: !1, line: 48, type: !230, isLocal: true, isDefinition: true, variable: [7 x i8]* @KW_ENTITY)
!230 = !DICompositeType(tag: DW_TAG_array_type, baseType: !87, size: 56, align: 8, elements: !231)
!231 = !{!232}
!232 = !DISubrange(count: 7)
!233 = !DIGlobalVariable(name: "KW_NDATA", scope: !0, file: !1, line: 68, type: !234, isLocal: true, isDefinition: true, variable: [6 x i8]* @KW_NDATA)
!234 = !DICompositeType(tag: DW_TAG_array_type, baseType: !87, size: 48, align: 8, elements: !235)
!235 = !{!236}
!236 = !DISubrange(count: 6)
!237 = !DIGlobalVariable(name: "KW_ATTLIST", scope: !0, file: !1, line: 35, type: !226, isLocal: true, isDefinition: true, variable: [8 x i8]* @KW_ATTLIST)
!238 = !DIGlobalVariable(name: "types", scope: !194, file: !1, line: 804, type: !239, isLocal: true, isDefinition: true, variable: [8 x i8*]* @attlist2.types)
!239 = !DICompositeType(tag: DW_TAG_array_type, baseType: !240, size: 512, align: 64, elements: !227)
!240 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !86)
!241 = !DIGlobalVariable(name: "KW_CDATA", scope: !0, file: !1, line: 37, type: !234, isLocal: true, isDefinition: true, variable: [6 x i8]* @KW_CDATA)
!242 = !DIGlobalVariable(name: "KW_ID", scope: !0, file: !1, line: 52, type: !243, isLocal: true, isDefinition: true, variable: [3 x i8]* @KW_ID)
!243 = !DICompositeType(tag: DW_TAG_array_type, baseType: !87, size: 24, align: 8, elements: !101)
!244 = !DIGlobalVariable(name: "KW_IDREF", scope: !0, file: !1, line: 54, type: !234, isLocal: true, isDefinition: true, variable: [6 x i8]* @KW_IDREF)
!245 = !DIGlobalVariable(name: "KW_IDREFS", scope: !0, file: !1, line: 56, type: !230, isLocal: true, isDefinition: true, variable: [7 x i8]* @KW_IDREFS)
!246 = !DIGlobalVariable(name: "KW_ENTITIES", scope: !0, file: !1, line: 45, type: !247, isLocal: true, isDefinition: true, variable: [9 x i8]* @KW_ENTITIES)
!247 = !DICompositeType(tag: DW_TAG_array_type, baseType: !87, size: 72, align: 8, elements: !248)
!248 = !{!249}
!249 = !DISubrange(count: 9)
!250 = !DIGlobalVariable(name: "KW_NMTOKEN", scope: !0, file: !1, line: 70, type: !226, isLocal: true, isDefinition: true, variable: [8 x i8]* @KW_NMTOKEN)
!251 = !DIGlobalVariable(name: "KW_NMTOKENS", scope: !0, file: !1, line: 72, type: !247, isLocal: true, isDefinition: true, variable: [9 x i8]* @KW_NMTOKENS)
!252 = !DIGlobalVariable(name: "KW_IMPLIED", scope: !0, file: !1, line: 62, type: !226, isLocal: true, isDefinition: true, variable: [8 x i8]* @KW_IMPLIED)
!253 = !DIGlobalVariable(name: "KW_REQUIRED", scope: !0, file: !1, line: 82, type: !247, isLocal: true, isDefinition: true, variable: [9 x i8]* @KW_REQUIRED)
!254 = !DIGlobalVariable(name: "KW_FIXED", scope: !0, file: !1, line: 50, type: !234, isLocal: true, isDefinition: true, variable: [6 x i8]* @KW_FIXED)
!255 = !DIGlobalVariable(name: "KW_ELEMENT", scope: !0, file: !1, line: 41, type: !226, isLocal: true, isDefinition: true, variable: [8 x i8]* @KW_ELEMENT)
!256 = !DIGlobalVariable(name: "KW_EMPTY", scope: !0, file: !1, line: 43, type: !234, isLocal: true, isDefinition: true, variable: [6 x i8]* @KW_EMPTY)
!257 = !DIGlobalVariable(name: "KW_ANY", scope: !0, file: !1, line: 33, type: !258, isLocal: true, isDefinition: true, variable: [4 x i8]* @KW_ANY)
!258 = !DICompositeType(tag: DW_TAG_array_type, baseType: !87, size: 32, align: 8, elements: !259)
!259 = !{!260}
!260 = !DISubrange(count: 4)
!261 = !DIGlobalVariable(name: "KW_PCDATA", scope: !0, file: !1, line: 78, type: !230, isLocal: true, isDefinition: true, variable: [7 x i8]* @KW_PCDATA)
!262 = !DIGlobalVariable(name: "KW_NOTATION", scope: !0, file: !1, line: 75, type: !247, isLocal: true, isDefinition: true, variable: [9 x i8]* @KW_NOTATION)
!263 = !DIGlobalVariable(name: "KW_SYSTEM", scope: !0, file: !1, line: 85, type: !230, isLocal: true, isDefinition: true, variable: [7 x i8]* @KW_SYSTEM)
!264 = !DIGlobalVariable(name: "KW_PUBLIC", scope: !0, file: !1, line: 80, type: !230, isLocal: true, isDefinition: true, variable: [7 x i8]* @KW_PUBLIC)
!265 = !{i32 2, !"Dwarf Version", i32 4}
!266 = !{i32 2, !"Debug Info Version", i32 3}
!267 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!268 = !DILocalVariable(name: "state", arg: 1, scope: !74, file: !1, line: 1316, type: !77)
!269 = !DIExpression()
!270 = !DILocation(line: 1316, column: 34, scope: !74)
!271 = !DILocation(line: 1318, column: 3, scope: !74)
!272 = !DILocation(line: 1318, column: 10, scope: !74)
!273 = !DILocation(line: 1318, column: 18, scope: !74)
!274 = !DILocation(line: 1324, column: 1, scope: !74)
!275 = !DILocalVariable(name: "state", arg: 1, scope: !173, file: !1, line: 128, type: !77)
!276 = !DILocation(line: 128, column: 23, scope: !173)
!277 = !DILocalVariable(name: "tok", arg: 2, scope: !173, file: !1, line: 129, type: !72)
!278 = !DILocation(line: 129, column: 13, scope: !173)
!279 = !DILocalVariable(name: "ptr", arg: 3, scope: !173, file: !1, line: 130, type: !86)
!280 = !DILocation(line: 130, column: 21, scope: !173)
!281 = !DILocalVariable(name: "end", arg: 4, scope: !173, file: !1, line: 131, type: !86)
!282 = !DILocation(line: 131, column: 21, scope: !173)
!283 = !DILocalVariable(name: "enc", arg: 5, scope: !173, file: !1, line: 132, type: !89)
!284 = !DILocation(line: 132, column: 25, scope: !173)
!285 = !DILocation(line: 134, column: 11, scope: !173)
!286 = !DILocation(line: 134, column: 3, scope: !173)
!287 = !DILocation(line: 136, column: 5, scope: !288)
!288 = distinct !DILexicalBlock(scope: !173, file: !1, line: 134, column: 16)
!289 = !DILocation(line: 136, column: 12, scope: !288)
!290 = !DILocation(line: 136, column: 20, scope: !288)
!291 = !DILocation(line: 137, column: 5, scope: !288)
!292 = !DILocation(line: 139, column: 5, scope: !288)
!293 = !DILocation(line: 139, column: 12, scope: !288)
!294 = !DILocation(line: 139, column: 20, scope: !288)
!295 = !DILocation(line: 140, column: 5, scope: !288)
!296 = !DILocation(line: 142, column: 5, scope: !288)
!297 = !DILocation(line: 142, column: 12, scope: !288)
!298 = !DILocation(line: 142, column: 20, scope: !288)
!299 = !DILocation(line: 143, column: 5, scope: !288)
!300 = !DILocation(line: 145, column: 5, scope: !288)
!301 = !DILocation(line: 145, column: 12, scope: !288)
!302 = !DILocation(line: 145, column: 20, scope: !288)
!303 = !DILocation(line: 146, column: 5, scope: !288)
!304 = !DILocation(line: 148, column: 5, scope: !288)
!305 = !DILocation(line: 150, column: 10, scope: !306)
!306 = distinct !DILexicalBlock(scope: !288, file: !1, line: 150, column: 9)
!307 = !DILocation(line: 150, column: 9, scope: !288)
!308 = !DILocation(line: 154, column: 7, scope: !306)
!309 = !DILocation(line: 155, column: 5, scope: !288)
!310 = !DILocation(line: 155, column: 12, scope: !288)
!311 = !DILocation(line: 155, column: 20, scope: !288)
!312 = !DILocation(line: 156, column: 5, scope: !288)
!313 = !DILocation(line: 158, column: 5, scope: !288)
!314 = !DILocation(line: 158, column: 12, scope: !288)
!315 = !DILocation(line: 158, column: 20, scope: !288)
!316 = !DILocation(line: 159, column: 5, scope: !288)
!317 = !DILocation(line: 161, column: 17, scope: !173)
!318 = !DILocation(line: 161, column: 24, scope: !173)
!319 = !DILocation(line: 161, column: 10, scope: !173)
!320 = !DILocation(line: 161, column: 3, scope: !173)
!321 = !DILocation(line: 162, column: 1, scope: !173)
!322 = !DILocalVariable(name: "state", arg: 1, scope: !176, file: !1, line: 165, type: !77)
!323 = !DILocation(line: 165, column: 23, scope: !176)
!324 = !DILocalVariable(name: "tok", arg: 2, scope: !176, file: !1, line: 166, type: !72)
!325 = !DILocation(line: 166, column: 13, scope: !176)
!326 = !DILocalVariable(name: "ptr", arg: 3, scope: !176, file: !1, line: 167, type: !86)
!327 = !DILocation(line: 167, column: 21, scope: !176)
!328 = !DILocalVariable(name: "end", arg: 4, scope: !176, file: !1, line: 168, type: !86)
!329 = !DILocation(line: 168, column: 21, scope: !176)
!330 = !DILocalVariable(name: "enc", arg: 5, scope: !176, file: !1, line: 169, type: !89)
!331 = !DILocation(line: 169, column: 25, scope: !176)
!332 = !DILocation(line: 171, column: 11, scope: !176)
!333 = !DILocation(line: 171, column: 3, scope: !176)
!334 = !DILocation(line: 173, column: 5, scope: !335)
!335 = distinct !DILexicalBlock(scope: !176, file: !1, line: 171, column: 16)
!336 = !DILocation(line: 175, column: 5, scope: !335)
!337 = !DILocation(line: 177, column: 5, scope: !335)
!338 = !DILocation(line: 179, column: 5, scope: !335)
!339 = !DILocation(line: 181, column: 10, scope: !340)
!340 = distinct !DILexicalBlock(scope: !335, file: !1, line: 181, column: 9)
!341 = !DILocation(line: 181, column: 9, scope: !335)
!342 = !DILocation(line: 185, column: 7, scope: !340)
!343 = !DILocation(line: 186, column: 5, scope: !335)
!344 = !DILocation(line: 186, column: 12, scope: !335)
!345 = !DILocation(line: 186, column: 20, scope: !335)
!346 = !DILocation(line: 187, column: 5, scope: !335)
!347 = !DILocation(line: 189, column: 5, scope: !335)
!348 = !DILocation(line: 189, column: 12, scope: !335)
!349 = !DILocation(line: 189, column: 20, scope: !335)
!350 = !DILocation(line: 190, column: 5, scope: !335)
!351 = !DILocation(line: 192, column: 17, scope: !176)
!352 = !DILocation(line: 192, column: 24, scope: !176)
!353 = !DILocation(line: 192, column: 10, scope: !176)
!354 = !DILocation(line: 192, column: 3, scope: !176)
!355 = !DILocation(line: 193, column: 1, scope: !176)
!356 = !DILocalVariable(name: "state", arg: 1, scope: !177, file: !1, line: 217, type: !77)
!357 = !DILocation(line: 217, column: 24, scope: !177)
!358 = !DILocalVariable(name: "tok", arg: 2, scope: !177, file: !1, line: 218, type: !72)
!359 = !DILocation(line: 218, column: 14, scope: !177)
!360 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !177, file: !1, line: 219, type: !86)
!361 = !DILocation(line: 219, column: 22, scope: !177)
!362 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !177, file: !1, line: 220, type: !86)
!363 = !DILocation(line: 220, column: 22, scope: !177)
!364 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !177, file: !1, line: 221, type: !89)
!365 = !DILocation(line: 221, column: 26, scope: !177)
!366 = !DILocation(line: 223, column: 11, scope: !177)
!367 = !DILocation(line: 223, column: 3, scope: !177)
!368 = !DILocation(line: 225, column: 5, scope: !369)
!369 = distinct !DILexicalBlock(scope: !177, file: !1, line: 223, column: 16)
!370 = !DILocation(line: 228, column: 5, scope: !369)
!371 = !DILocation(line: 228, column: 12, scope: !369)
!372 = !DILocation(line: 228, column: 20, scope: !369)
!373 = !DILocation(line: 229, column: 5, scope: !369)
!374 = !DILocation(line: 231, column: 17, scope: !177)
!375 = !DILocation(line: 231, column: 24, scope: !177)
!376 = !DILocation(line: 231, column: 10, scope: !177)
!377 = !DILocation(line: 231, column: 3, scope: !177)
!378 = !DILocation(line: 232, column: 1, scope: !177)
!379 = !DILocalVariable(name: "UNUSED_state", arg: 1, scope: !220, file: !1, line: 1295, type: !77)
!380 = !DILocation(line: 1295, column: 21, scope: !220)
!381 = !DILocalVariable(name: "UNUSED_tok", arg: 2, scope: !220, file: !1, line: 1296, type: !72)
!382 = !DILocation(line: 1296, column: 11, scope: !220)
!383 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !220, file: !1, line: 1297, type: !86)
!384 = !DILocation(line: 1297, column: 19, scope: !220)
!385 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !220, file: !1, line: 1298, type: !86)
!386 = !DILocation(line: 1298, column: 19, scope: !220)
!387 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !220, file: !1, line: 1299, type: !89)
!388 = !DILocation(line: 1299, column: 23, scope: !220)
!389 = !DILocation(line: 1301, column: 3, scope: !220)
!390 = !DILocalVariable(name: "state", arg: 1, scope: !221, file: !1, line: 1305, type: !77)
!391 = !DILocation(line: 1305, column: 22, scope: !221)
!392 = !DILocalVariable(name: "tok", arg: 2, scope: !221, file: !1, line: 1305, type: !72)
!393 = !DILocation(line: 1305, column: 33, scope: !221)
!394 = !DILocation(line: 1311, column: 3, scope: !221)
!395 = !DILocation(line: 1311, column: 10, scope: !221)
!396 = !DILocation(line: 1311, column: 18, scope: !221)
!397 = !DILocation(line: 1312, column: 3, scope: !221)
!398 = !DILocalVariable(name: "state", arg: 1, scope: !178, file: !1, line: 235, type: !77)
!399 = !DILocation(line: 235, column: 24, scope: !178)
!400 = !DILocalVariable(name: "tok", arg: 2, scope: !178, file: !1, line: 236, type: !72)
!401 = !DILocation(line: 236, column: 14, scope: !178)
!402 = !DILocalVariable(name: "ptr", arg: 3, scope: !178, file: !1, line: 237, type: !86)
!403 = !DILocation(line: 237, column: 22, scope: !178)
!404 = !DILocalVariable(name: "end", arg: 4, scope: !178, file: !1, line: 238, type: !86)
!405 = !DILocation(line: 238, column: 22, scope: !178)
!406 = !DILocalVariable(name: "enc", arg: 5, scope: !178, file: !1, line: 239, type: !89)
!407 = !DILocation(line: 239, column: 26, scope: !178)
!408 = !DILocation(line: 241, column: 11, scope: !178)
!409 = !DILocation(line: 241, column: 3, scope: !178)
!410 = !DILocation(line: 243, column: 5, scope: !411)
!411 = distinct !DILexicalBlock(scope: !178, file: !1, line: 241, column: 16)
!412 = !DILocation(line: 245, column: 5, scope: !411)
!413 = !DILocation(line: 245, column: 12, scope: !411)
!414 = !DILocation(line: 245, column: 20, scope: !411)
!415 = !DILocation(line: 246, column: 5, scope: !411)
!416 = !DILocation(line: 248, column: 5, scope: !411)
!417 = !DILocation(line: 248, column: 12, scope: !411)
!418 = !DILocation(line: 248, column: 20, scope: !411)
!419 = !DILocation(line: 249, column: 5, scope: !411)
!420 = !DILocation(line: 251, column: 9, scope: !421)
!421 = distinct !DILexicalBlock(scope: !411, file: !1, line: 251, column: 9)
!422 = !DILocation(line: 251, column: 9, scope: !411)
!423 = !DILocation(line: 252, column: 7, scope: !424)
!424 = distinct !DILexicalBlock(scope: !421, file: !1, line: 251, column: 56)
!425 = !DILocation(line: 252, column: 14, scope: !424)
!426 = !DILocation(line: 252, column: 22, scope: !424)
!427 = !DILocation(line: 253, column: 7, scope: !424)
!428 = !DILocation(line: 255, column: 9, scope: !429)
!429 = distinct !DILexicalBlock(scope: !411, file: !1, line: 255, column: 9)
!430 = !DILocation(line: 255, column: 9, scope: !411)
!431 = !DILocation(line: 256, column: 7, scope: !432)
!432 = distinct !DILexicalBlock(scope: !429, file: !1, line: 255, column: 56)
!433 = !DILocation(line: 256, column: 14, scope: !432)
!434 = !DILocation(line: 256, column: 22, scope: !432)
!435 = !DILocation(line: 257, column: 7, scope: !432)
!436 = !DILocation(line: 259, column: 5, scope: !411)
!437 = !DILocation(line: 261, column: 17, scope: !178)
!438 = !DILocation(line: 261, column: 24, scope: !178)
!439 = !DILocation(line: 261, column: 10, scope: !178)
!440 = !DILocation(line: 261, column: 3, scope: !178)
!441 = !DILocation(line: 262, column: 1, scope: !178)
!442 = !DILocalVariable(name: "state", arg: 1, scope: !179, file: !1, line: 336, type: !77)
!443 = !DILocation(line: 336, column: 30, scope: !179)
!444 = !DILocalVariable(name: "tok", arg: 2, scope: !179, file: !1, line: 337, type: !72)
!445 = !DILocation(line: 337, column: 20, scope: !179)
!446 = !DILocalVariable(name: "ptr", arg: 3, scope: !179, file: !1, line: 338, type: !86)
!447 = !DILocation(line: 338, column: 28, scope: !179)
!448 = !DILocalVariable(name: "end", arg: 4, scope: !179, file: !1, line: 339, type: !86)
!449 = !DILocation(line: 339, column: 28, scope: !179)
!450 = !DILocalVariable(name: "enc", arg: 5, scope: !179, file: !1, line: 340, type: !89)
!451 = !DILocation(line: 340, column: 32, scope: !179)
!452 = !DILocation(line: 342, column: 11, scope: !179)
!453 = !DILocation(line: 342, column: 3, scope: !179)
!454 = !DILocation(line: 344, column: 5, scope: !455)
!455 = distinct !DILexicalBlock(scope: !179, file: !1, line: 342, column: 16)
!456 = !DILocation(line: 346, column: 9, scope: !457)
!457 = distinct !DILexicalBlock(scope: !455, file: !1, line: 346, column: 9)
!458 = !DILocation(line: 346, column: 9, scope: !455)
!459 = !DILocation(line: 350, column: 7, scope: !460)
!460 = distinct !DILexicalBlock(scope: !457, file: !1, line: 349, column: 41)
!461 = !DILocation(line: 350, column: 14, scope: !460)
!462 = !DILocation(line: 350, column: 22, scope: !460)
!463 = !DILocation(line: 351, column: 7, scope: !460)
!464 = !DILocation(line: 353, column: 9, scope: !465)
!465 = distinct !DILexicalBlock(scope: !455, file: !1, line: 353, column: 9)
!466 = !DILocation(line: 353, column: 9, scope: !455)
!467 = !DILocation(line: 357, column: 7, scope: !468)
!468 = distinct !DILexicalBlock(scope: !465, file: !1, line: 356, column: 42)
!469 = !DILocation(line: 357, column: 14, scope: !468)
!470 = !DILocation(line: 357, column: 22, scope: !468)
!471 = !DILocation(line: 358, column: 7, scope: !468)
!472 = !DILocation(line: 360, column: 9, scope: !473)
!473 = distinct !DILexicalBlock(scope: !455, file: !1, line: 360, column: 9)
!474 = !DILocation(line: 360, column: 9, scope: !455)
!475 = !DILocation(line: 364, column: 7, scope: !476)
!476 = distinct !DILexicalBlock(scope: !473, file: !1, line: 363, column: 42)
!477 = !DILocation(line: 364, column: 14, scope: !476)
!478 = !DILocation(line: 364, column: 22, scope: !476)
!479 = !DILocation(line: 365, column: 7, scope: !476)
!480 = !DILocation(line: 367, column: 9, scope: !481)
!481 = distinct !DILexicalBlock(scope: !455, file: !1, line: 367, column: 9)
!482 = !DILocation(line: 367, column: 9, scope: !455)
!483 = !DILocation(line: 371, column: 7, scope: !484)
!484 = distinct !DILexicalBlock(scope: !481, file: !1, line: 370, column: 43)
!485 = !DILocation(line: 371, column: 14, scope: !484)
!486 = !DILocation(line: 371, column: 22, scope: !484)
!487 = !DILocation(line: 372, column: 7, scope: !484)
!488 = !DILocation(line: 374, column: 5, scope: !455)
!489 = !DILocation(line: 376, column: 5, scope: !455)
!490 = !DILocation(line: 378, column: 5, scope: !455)
!491 = !DILocation(line: 380, column: 5, scope: !455)
!492 = !DILocation(line: 382, column: 5, scope: !455)
!493 = !DILocation(line: 382, column: 12, scope: !455)
!494 = !DILocation(line: 382, column: 20, scope: !455)
!495 = !DILocation(line: 383, column: 5, scope: !455)
!496 = !DILocation(line: 385, column: 5, scope: !455)
!497 = !DILocation(line: 387, column: 17, scope: !179)
!498 = !DILocation(line: 387, column: 24, scope: !179)
!499 = !DILocation(line: 387, column: 10, scope: !179)
!500 = !DILocation(line: 387, column: 3, scope: !179)
!501 = !DILocation(line: 388, column: 1, scope: !179)
!502 = !DILocalVariable(name: "state", arg: 1, scope: !216, file: !1, line: 196, type: !77)
!503 = !DILocation(line: 196, column: 23, scope: !216)
!504 = !DILocalVariable(name: "tok", arg: 2, scope: !216, file: !1, line: 197, type: !72)
!505 = !DILocation(line: 197, column: 13, scope: !216)
!506 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !216, file: !1, line: 198, type: !86)
!507 = !DILocation(line: 198, column: 21, scope: !216)
!508 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !216, file: !1, line: 199, type: !86)
!509 = !DILocation(line: 199, column: 21, scope: !216)
!510 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !216, file: !1, line: 200, type: !89)
!511 = !DILocation(line: 200, column: 25, scope: !216)
!512 = !DILocation(line: 202, column: 11, scope: !216)
!513 = !DILocation(line: 202, column: 3, scope: !216)
!514 = !DILocation(line: 204, column: 5, scope: !515)
!515 = distinct !DILexicalBlock(scope: !216, file: !1, line: 202, column: 16)
!516 = !DILocation(line: 206, column: 5, scope: !515)
!517 = !DILocation(line: 208, column: 5, scope: !515)
!518 = !DILocation(line: 210, column: 5, scope: !515)
!519 = !DILocation(line: 210, column: 12, scope: !515)
!520 = !DILocation(line: 210, column: 20, scope: !515)
!521 = !DILocation(line: 211, column: 5, scope: !515)
!522 = !DILocation(line: 213, column: 17, scope: !216)
!523 = !DILocation(line: 213, column: 24, scope: !216)
!524 = !DILocation(line: 213, column: 10, scope: !216)
!525 = !DILocation(line: 213, column: 3, scope: !216)
!526 = !DILocation(line: 214, column: 1, scope: !216)
!527 = !DILocalVariable(name: "state", arg: 1, scope: !217, file: !1, line: 282, type: !77)
!528 = !DILocation(line: 282, column: 24, scope: !217)
!529 = !DILocalVariable(name: "tok", arg: 2, scope: !217, file: !1, line: 283, type: !72)
!530 = !DILocation(line: 283, column: 14, scope: !217)
!531 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !217, file: !1, line: 284, type: !86)
!532 = !DILocation(line: 284, column: 22, scope: !217)
!533 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !217, file: !1, line: 285, type: !86)
!534 = !DILocation(line: 285, column: 22, scope: !217)
!535 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !217, file: !1, line: 286, type: !89)
!536 = !DILocation(line: 286, column: 26, scope: !217)
!537 = !DILocation(line: 288, column: 11, scope: !217)
!538 = !DILocation(line: 288, column: 3, scope: !217)
!539 = !DILocation(line: 290, column: 5, scope: !540)
!540 = distinct !DILexicalBlock(scope: !217, file: !1, line: 288, column: 16)
!541 = !DILocation(line: 292, column: 5, scope: !540)
!542 = !DILocation(line: 292, column: 12, scope: !540)
!543 = !DILocation(line: 292, column: 20, scope: !540)
!544 = !DILocation(line: 293, column: 5, scope: !540)
!545 = !DILocation(line: 295, column: 17, scope: !217)
!546 = !DILocation(line: 295, column: 24, scope: !217)
!547 = !DILocation(line: 295, column: 10, scope: !217)
!548 = !DILocation(line: 295, column: 3, scope: !217)
!549 = !DILocation(line: 296, column: 1, scope: !217)
!550 = !DILocalVariable(name: "state", arg: 1, scope: !219, file: !1, line: 265, type: !77)
!551 = !DILocation(line: 265, column: 24, scope: !219)
!552 = !DILocalVariable(name: "tok", arg: 2, scope: !219, file: !1, line: 266, type: !72)
!553 = !DILocation(line: 266, column: 14, scope: !219)
!554 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !219, file: !1, line: 267, type: !86)
!555 = !DILocation(line: 267, column: 22, scope: !219)
!556 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !219, file: !1, line: 268, type: !86)
!557 = !DILocation(line: 268, column: 22, scope: !219)
!558 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !219, file: !1, line: 269, type: !89)
!559 = !DILocation(line: 269, column: 26, scope: !219)
!560 = !DILocation(line: 271, column: 11, scope: !219)
!561 = !DILocation(line: 271, column: 3, scope: !219)
!562 = !DILocation(line: 273, column: 5, scope: !563)
!563 = distinct !DILexicalBlock(scope: !219, file: !1, line: 271, column: 16)
!564 = !DILocation(line: 275, column: 5, scope: !563)
!565 = !DILocation(line: 275, column: 12, scope: !563)
!566 = !DILocation(line: 275, column: 20, scope: !563)
!567 = !DILocation(line: 276, column: 5, scope: !563)
!568 = !DILocation(line: 278, column: 17, scope: !219)
!569 = !DILocation(line: 278, column: 24, scope: !219)
!570 = !DILocation(line: 278, column: 10, scope: !219)
!571 = !DILocation(line: 278, column: 3, scope: !219)
!572 = !DILocation(line: 279, column: 1, scope: !219)
!573 = !DILocalVariable(name: "state", arg: 1, scope: !180, file: !1, line: 438, type: !77)
!574 = !DILocation(line: 438, column: 23, scope: !180)
!575 = !DILocalVariable(name: "tok", arg: 2, scope: !180, file: !1, line: 439, type: !72)
!576 = !DILocation(line: 439, column: 13, scope: !180)
!577 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !180, file: !1, line: 440, type: !86)
!578 = !DILocation(line: 440, column: 21, scope: !180)
!579 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !180, file: !1, line: 441, type: !86)
!580 = !DILocation(line: 441, column: 21, scope: !180)
!581 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !180, file: !1, line: 442, type: !89)
!582 = !DILocation(line: 442, column: 25, scope: !180)
!583 = !DILocation(line: 444, column: 11, scope: !180)
!584 = !DILocation(line: 444, column: 3, scope: !180)
!585 = !DILocation(line: 446, column: 5, scope: !586)
!586 = distinct !DILexicalBlock(scope: !180, file: !1, line: 444, column: 16)
!587 = !DILocation(line: 448, column: 5, scope: !586)
!588 = !DILocation(line: 448, column: 12, scope: !586)
!589 = !DILocation(line: 448, column: 20, scope: !586)
!590 = !DILocation(line: 449, column: 5, scope: !586)
!591 = !DILocation(line: 451, column: 5, scope: !586)
!592 = !DILocation(line: 451, column: 12, scope: !586)
!593 = !DILocation(line: 451, column: 20, scope: !586)
!594 = !DILocation(line: 452, column: 5, scope: !586)
!595 = !DILocation(line: 454, column: 17, scope: !180)
!596 = !DILocation(line: 454, column: 24, scope: !180)
!597 = !DILocation(line: 454, column: 10, scope: !180)
!598 = !DILocation(line: 454, column: 3, scope: !180)
!599 = !DILocation(line: 455, column: 1, scope: !180)
!600 = !DILocalVariable(name: "state", arg: 1, scope: !192, file: !1, line: 754, type: !77)
!601 = !DILocation(line: 754, column: 24, scope: !192)
!602 = !DILocalVariable(name: "tok", arg: 2, scope: !192, file: !1, line: 755, type: !72)
!603 = !DILocation(line: 755, column: 14, scope: !192)
!604 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !192, file: !1, line: 756, type: !86)
!605 = !DILocation(line: 756, column: 22, scope: !192)
!606 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !192, file: !1, line: 757, type: !86)
!607 = !DILocation(line: 757, column: 22, scope: !192)
!608 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !192, file: !1, line: 758, type: !89)
!609 = !DILocation(line: 758, column: 26, scope: !192)
!610 = !DILocation(line: 760, column: 11, scope: !192)
!611 = !DILocation(line: 760, column: 3, scope: !192)
!612 = !DILocation(line: 762, column: 5, scope: !613)
!613 = distinct !DILexicalBlock(scope: !192, file: !1, line: 760, column: 16)
!614 = !DILocation(line: 765, column: 5, scope: !613)
!615 = !DILocation(line: 765, column: 12, scope: !613)
!616 = !DILocation(line: 765, column: 20, scope: !613)
!617 = !DILocation(line: 766, column: 5, scope: !613)
!618 = !DILocation(line: 768, column: 17, scope: !192)
!619 = !DILocation(line: 768, column: 24, scope: !192)
!620 = !DILocation(line: 768, column: 10, scope: !192)
!621 = !DILocation(line: 768, column: 3, scope: !192)
!622 = !DILocation(line: 769, column: 1, scope: !192)
!623 = !DILocalVariable(name: "state", arg: 1, scope: !202, file: !1, line: 985, type: !77)
!624 = !DILocation(line: 985, column: 24, scope: !202)
!625 = !DILocalVariable(name: "tok", arg: 2, scope: !202, file: !1, line: 986, type: !72)
!626 = !DILocation(line: 986, column: 14, scope: !202)
!627 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !202, file: !1, line: 987, type: !86)
!628 = !DILocation(line: 987, column: 22, scope: !202)
!629 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !202, file: !1, line: 988, type: !86)
!630 = !DILocation(line: 988, column: 22, scope: !202)
!631 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !202, file: !1, line: 989, type: !89)
!632 = !DILocation(line: 989, column: 26, scope: !202)
!633 = !DILocation(line: 991, column: 11, scope: !202)
!634 = !DILocation(line: 991, column: 3, scope: !202)
!635 = !DILocation(line: 993, column: 5, scope: !636)
!636 = distinct !DILexicalBlock(scope: !202, file: !1, line: 991, column: 16)
!637 = !DILocation(line: 996, column: 5, scope: !636)
!638 = !DILocation(line: 996, column: 12, scope: !636)
!639 = !DILocation(line: 996, column: 20, scope: !636)
!640 = !DILocation(line: 997, column: 5, scope: !636)
!641 = !DILocation(line: 999, column: 17, scope: !202)
!642 = !DILocation(line: 999, column: 24, scope: !202)
!643 = !DILocation(line: 999, column: 10, scope: !202)
!644 = !DILocation(line: 999, column: 3, scope: !202)
!645 = !DILocation(line: 1000, column: 1, scope: !202)
!646 = !DILocalVariable(name: "state", arg: 1, scope: !210, file: !1, line: 657, type: !77)
!647 = !DILocation(line: 657, column: 25, scope: !210)
!648 = !DILocalVariable(name: "tok", arg: 2, scope: !210, file: !1, line: 658, type: !72)
!649 = !DILocation(line: 658, column: 15, scope: !210)
!650 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !210, file: !1, line: 659, type: !86)
!651 = !DILocation(line: 659, column: 23, scope: !210)
!652 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !210, file: !1, line: 660, type: !86)
!653 = !DILocation(line: 660, column: 23, scope: !210)
!654 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !210, file: !1, line: 661, type: !89)
!655 = !DILocation(line: 661, column: 27, scope: !210)
!656 = !DILocation(line: 663, column: 11, scope: !210)
!657 = !DILocation(line: 663, column: 3, scope: !210)
!658 = !DILocation(line: 665, column: 5, scope: !659)
!659 = distinct !DILexicalBlock(scope: !210, file: !1, line: 663, column: 16)
!660 = !DILocation(line: 667, column: 5, scope: !659)
!661 = !DILocation(line: 667, column: 12, scope: !659)
!662 = !DILocation(line: 667, column: 20, scope: !659)
!663 = !DILocation(line: 668, column: 5, scope: !659)
!664 = !DILocation(line: 670, column: 17, scope: !210)
!665 = !DILocation(line: 670, column: 24, scope: !210)
!666 = !DILocation(line: 670, column: 10, scope: !210)
!667 = !DILocation(line: 670, column: 3, scope: !210)
!668 = !DILocation(line: 671, column: 1, scope: !210)
!669 = !DILocalVariable(name: "state", arg: 1, scope: !215, file: !1, line: 319, type: !77)
!670 = !DILocation(line: 319, column: 24, scope: !215)
!671 = !DILocalVariable(name: "tok", arg: 2, scope: !215, file: !1, line: 320, type: !72)
!672 = !DILocation(line: 320, column: 14, scope: !215)
!673 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !215, file: !1, line: 321, type: !86)
!674 = !DILocation(line: 321, column: 22, scope: !215)
!675 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !215, file: !1, line: 322, type: !86)
!676 = !DILocation(line: 322, column: 22, scope: !215)
!677 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !215, file: !1, line: 323, type: !89)
!678 = !DILocation(line: 323, column: 26, scope: !215)
!679 = !DILocation(line: 325, column: 11, scope: !215)
!680 = !DILocation(line: 325, column: 3, scope: !215)
!681 = !DILocation(line: 327, column: 5, scope: !682)
!682 = distinct !DILexicalBlock(scope: !215, file: !1, line: 325, column: 16)
!683 = !DILocation(line: 329, column: 5, scope: !682)
!684 = !DILocation(line: 329, column: 12, scope: !682)
!685 = !DILocation(line: 329, column: 20, scope: !682)
!686 = !DILocation(line: 330, column: 5, scope: !682)
!687 = !DILocation(line: 332, column: 17, scope: !215)
!688 = !DILocation(line: 332, column: 24, scope: !215)
!689 = !DILocation(line: 332, column: 10, scope: !215)
!690 = !DILocation(line: 332, column: 3, scope: !215)
!691 = !DILocation(line: 333, column: 1, scope: !215)
!692 = !DILocalVariable(name: "state", arg: 1, scope: !181, file: !1, line: 458, type: !77)
!693 = !DILocation(line: 458, column: 23, scope: !181)
!694 = !DILocalVariable(name: "tok", arg: 2, scope: !181, file: !1, line: 459, type: !72)
!695 = !DILocation(line: 459, column: 13, scope: !181)
!696 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !181, file: !1, line: 460, type: !86)
!697 = !DILocation(line: 460, column: 21, scope: !181)
!698 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !181, file: !1, line: 461, type: !86)
!699 = !DILocation(line: 461, column: 21, scope: !181)
!700 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !181, file: !1, line: 462, type: !89)
!701 = !DILocation(line: 462, column: 25, scope: !181)
!702 = !DILocation(line: 464, column: 11, scope: !181)
!703 = !DILocation(line: 464, column: 3, scope: !181)
!704 = !DILocation(line: 466, column: 5, scope: !705)
!705 = distinct !DILexicalBlock(scope: !181, file: !1, line: 464, column: 16)
!706 = !DILocation(line: 468, column: 5, scope: !705)
!707 = !DILocation(line: 468, column: 12, scope: !705)
!708 = !DILocation(line: 468, column: 20, scope: !705)
!709 = !DILocation(line: 469, column: 5, scope: !705)
!710 = !DILocation(line: 471, column: 17, scope: !181)
!711 = !DILocation(line: 471, column: 24, scope: !181)
!712 = !DILocation(line: 471, column: 10, scope: !181)
!713 = !DILocation(line: 471, column: 3, scope: !181)
!714 = !DILocation(line: 472, column: 1, scope: !181)
!715 = !DILocalVariable(name: "state", arg: 1, scope: !187, file: !1, line: 475, type: !77)
!716 = !DILocation(line: 475, column: 23, scope: !187)
!717 = !DILocalVariable(name: "tok", arg: 2, scope: !187, file: !1, line: 476, type: !72)
!718 = !DILocation(line: 476, column: 13, scope: !187)
!719 = !DILocalVariable(name: "ptr", arg: 3, scope: !187, file: !1, line: 477, type: !86)
!720 = !DILocation(line: 477, column: 21, scope: !187)
!721 = !DILocalVariable(name: "end", arg: 4, scope: !187, file: !1, line: 478, type: !86)
!722 = !DILocation(line: 478, column: 21, scope: !187)
!723 = !DILocalVariable(name: "enc", arg: 5, scope: !187, file: !1, line: 479, type: !89)
!724 = !DILocation(line: 479, column: 25, scope: !187)
!725 = !DILocation(line: 481, column: 11, scope: !187)
!726 = !DILocation(line: 481, column: 3, scope: !187)
!727 = !DILocation(line: 483, column: 5, scope: !728)
!728 = distinct !DILexicalBlock(scope: !187, file: !1, line: 481, column: 16)
!729 = !DILocation(line: 485, column: 9, scope: !730)
!730 = distinct !DILexicalBlock(scope: !728, file: !1, line: 485, column: 9)
!731 = !DILocation(line: 485, column: 9, scope: !728)
!732 = !DILocation(line: 486, column: 7, scope: !733)
!733 = distinct !DILexicalBlock(scope: !730, file: !1, line: 485, column: 56)
!734 = !DILocation(line: 486, column: 14, scope: !733)
!735 = !DILocation(line: 486, column: 22, scope: !733)
!736 = !DILocation(line: 487, column: 7, scope: !733)
!737 = !DILocation(line: 489, column: 9, scope: !738)
!738 = distinct !DILexicalBlock(scope: !728, file: !1, line: 489, column: 9)
!739 = !DILocation(line: 489, column: 9, scope: !728)
!740 = !DILocation(line: 490, column: 7, scope: !741)
!741 = distinct !DILexicalBlock(scope: !738, file: !1, line: 489, column: 56)
!742 = !DILocation(line: 490, column: 14, scope: !741)
!743 = !DILocation(line: 490, column: 22, scope: !741)
!744 = !DILocation(line: 491, column: 7, scope: !741)
!745 = !DILocation(line: 493, column: 5, scope: !728)
!746 = !DILocation(line: 495, column: 5, scope: !728)
!747 = !DILocation(line: 495, column: 12, scope: !728)
!748 = !DILocation(line: 495, column: 20, scope: !728)
!749 = !DILocation(line: 496, column: 5, scope: !728)
!750 = !DILocation(line: 496, column: 12, scope: !728)
!751 = !DILocation(line: 496, column: 22, scope: !728)
!752 = !DILocation(line: 497, column: 5, scope: !728)
!753 = !DILocation(line: 499, column: 17, scope: !187)
!754 = !DILocation(line: 499, column: 24, scope: !187)
!755 = !DILocation(line: 499, column: 10, scope: !187)
!756 = !DILocation(line: 499, column: 3, scope: !187)
!757 = !DILocation(line: 500, column: 1, scope: !187)
!758 = !DILocalVariable(name: "state", arg: 1, scope: !182, file: !1, line: 578, type: !77)
!759 = !DILocation(line: 578, column: 23, scope: !182)
!760 = !DILocalVariable(name: "tok", arg: 2, scope: !182, file: !1, line: 579, type: !72)
!761 = !DILocation(line: 579, column: 13, scope: !182)
!762 = !DILocalVariable(name: "ptr", arg: 3, scope: !182, file: !1, line: 580, type: !86)
!763 = !DILocation(line: 580, column: 21, scope: !182)
!764 = !DILocalVariable(name: "end", arg: 4, scope: !182, file: !1, line: 581, type: !86)
!765 = !DILocation(line: 581, column: 21, scope: !182)
!766 = !DILocalVariable(name: "enc", arg: 5, scope: !182, file: !1, line: 582, type: !89)
!767 = !DILocation(line: 582, column: 25, scope: !182)
!768 = !DILocation(line: 584, column: 11, scope: !182)
!769 = !DILocation(line: 584, column: 3, scope: !182)
!770 = !DILocation(line: 586, column: 5, scope: !771)
!771 = distinct !DILexicalBlock(scope: !182, file: !1, line: 584, column: 16)
!772 = !DILocation(line: 588, column: 9, scope: !773)
!773 = distinct !DILexicalBlock(scope: !771, file: !1, line: 588, column: 9)
!774 = !DILocation(line: 588, column: 9, scope: !771)
!775 = !DILocation(line: 589, column: 7, scope: !776)
!776 = distinct !DILexicalBlock(scope: !773, file: !1, line: 588, column: 56)
!777 = !DILocation(line: 589, column: 14, scope: !776)
!778 = !DILocation(line: 589, column: 22, scope: !776)
!779 = !DILocation(line: 590, column: 7, scope: !776)
!780 = !DILocation(line: 592, column: 9, scope: !781)
!781 = distinct !DILexicalBlock(scope: !771, file: !1, line: 592, column: 9)
!782 = !DILocation(line: 592, column: 9, scope: !771)
!783 = !DILocation(line: 593, column: 7, scope: !784)
!784 = distinct !DILexicalBlock(scope: !781, file: !1, line: 592, column: 56)
!785 = !DILocation(line: 593, column: 14, scope: !784)
!786 = !DILocation(line: 593, column: 22, scope: !784)
!787 = !DILocation(line: 594, column: 7, scope: !784)
!788 = !DILocation(line: 596, column: 5, scope: !771)
!789 = !DILocation(line: 598, column: 5, scope: !771)
!790 = !DILocation(line: 598, column: 12, scope: !771)
!791 = !DILocation(line: 598, column: 20, scope: !771)
!792 = !DILocation(line: 599, column: 5, scope: !771)
!793 = !DILocation(line: 599, column: 12, scope: !771)
!794 = !DILocation(line: 599, column: 22, scope: !771)
!795 = !DILocation(line: 600, column: 5, scope: !771)
!796 = !DILocation(line: 602, column: 17, scope: !182)
!797 = !DILocation(line: 602, column: 24, scope: !182)
!798 = !DILocation(line: 602, column: 10, scope: !182)
!799 = !DILocation(line: 602, column: 3, scope: !182)
!800 = !DILocation(line: 603, column: 1, scope: !182)
!801 = !DILocalVariable(name: "state", arg: 1, scope: !183, file: !1, line: 623, type: !77)
!802 = !DILocation(line: 623, column: 23, scope: !183)
!803 = !DILocalVariable(name: "tok", arg: 2, scope: !183, file: !1, line: 624, type: !72)
!804 = !DILocation(line: 624, column: 13, scope: !183)
!805 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !183, file: !1, line: 625, type: !86)
!806 = !DILocation(line: 625, column: 21, scope: !183)
!807 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !183, file: !1, line: 626, type: !86)
!808 = !DILocation(line: 626, column: 21, scope: !183)
!809 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !183, file: !1, line: 627, type: !89)
!810 = !DILocation(line: 627, column: 25, scope: !183)
!811 = !DILocation(line: 629, column: 11, scope: !183)
!812 = !DILocation(line: 629, column: 3, scope: !183)
!813 = !DILocation(line: 631, column: 5, scope: !814)
!814 = distinct !DILexicalBlock(scope: !183, file: !1, line: 629, column: 16)
!815 = !DILocation(line: 633, column: 5, scope: !814)
!816 = !DILocation(line: 633, column: 12, scope: !814)
!817 = !DILocation(line: 633, column: 20, scope: !814)
!818 = !DILocation(line: 634, column: 5, scope: !814)
!819 = !DILocation(line: 636, column: 17, scope: !183)
!820 = !DILocation(line: 636, column: 24, scope: !183)
!821 = !DILocation(line: 636, column: 10, scope: !183)
!822 = !DILocation(line: 636, column: 3, scope: !183)
!823 = !DILocation(line: 637, column: 1, scope: !183)
!824 = !DILocalVariable(name: "state", arg: 1, scope: !185, file: !1, line: 606, type: !77)
!825 = !DILocation(line: 606, column: 23, scope: !185)
!826 = !DILocalVariable(name: "tok", arg: 2, scope: !185, file: !1, line: 607, type: !72)
!827 = !DILocation(line: 607, column: 13, scope: !185)
!828 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !185, file: !1, line: 608, type: !86)
!829 = !DILocation(line: 608, column: 21, scope: !185)
!830 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !185, file: !1, line: 609, type: !86)
!831 = !DILocation(line: 609, column: 21, scope: !185)
!832 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !185, file: !1, line: 610, type: !89)
!833 = !DILocation(line: 610, column: 25, scope: !185)
!834 = !DILocation(line: 612, column: 11, scope: !185)
!835 = !DILocation(line: 612, column: 3, scope: !185)
!836 = !DILocation(line: 614, column: 5, scope: !837)
!837 = distinct !DILexicalBlock(scope: !185, file: !1, line: 612, column: 16)
!838 = !DILocation(line: 616, column: 5, scope: !837)
!839 = !DILocation(line: 616, column: 12, scope: !837)
!840 = !DILocation(line: 616, column: 20, scope: !837)
!841 = !DILocation(line: 617, column: 5, scope: !837)
!842 = !DILocation(line: 619, column: 17, scope: !185)
!843 = !DILocation(line: 619, column: 24, scope: !185)
!844 = !DILocation(line: 619, column: 10, scope: !185)
!845 = !DILocation(line: 619, column: 3, scope: !185)
!846 = !DILocation(line: 620, column: 1, scope: !185)
!847 = !DILocalVariable(name: "state", arg: 1, scope: !186, file: !1, line: 1278, type: !77)
!848 = !DILocation(line: 1278, column: 25, scope: !186)
!849 = !DILocalVariable(name: "tok", arg: 2, scope: !186, file: !1, line: 1279, type: !72)
!850 = !DILocation(line: 1279, column: 15, scope: !186)
!851 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !186, file: !1, line: 1280, type: !86)
!852 = !DILocation(line: 1280, column: 23, scope: !186)
!853 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !186, file: !1, line: 1281, type: !86)
!854 = !DILocation(line: 1281, column: 23, scope: !186)
!855 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !186, file: !1, line: 1282, type: !89)
!856 = !DILocation(line: 1282, column: 27, scope: !186)
!857 = !DILocation(line: 1284, column: 11, scope: !186)
!858 = !DILocation(line: 1284, column: 3, scope: !186)
!859 = !DILocation(line: 1286, column: 12, scope: !860)
!860 = distinct !DILexicalBlock(scope: !186, file: !1, line: 1284, column: 16)
!861 = !DILocation(line: 1286, column: 19, scope: !860)
!862 = !DILocation(line: 1286, column: 5, scope: !860)
!863 = !DILocation(line: 1288, column: 5, scope: !860)
!864 = !DILocation(line: 1289, column: 12, scope: !860)
!865 = !DILocation(line: 1289, column: 19, scope: !860)
!866 = !DILocation(line: 1289, column: 5, scope: !860)
!867 = !DILocation(line: 1291, column: 17, scope: !186)
!868 = !DILocation(line: 1291, column: 24, scope: !186)
!869 = !DILocation(line: 1291, column: 10, scope: !186)
!870 = !DILocation(line: 1291, column: 3, scope: !186)
!871 = !DILocation(line: 1292, column: 1, scope: !186)
!872 = !DILocalVariable(name: "state", arg: 1, scope: !184, file: !1, line: 640, type: !77)
!873 = !DILocation(line: 640, column: 24, scope: !184)
!874 = !DILocalVariable(name: "tok", arg: 2, scope: !184, file: !1, line: 641, type: !72)
!875 = !DILocation(line: 641, column: 14, scope: !184)
!876 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !184, file: !1, line: 642, type: !86)
!877 = !DILocation(line: 642, column: 22, scope: !184)
!878 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !184, file: !1, line: 643, type: !86)
!879 = !DILocation(line: 643, column: 22, scope: !184)
!880 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !184, file: !1, line: 644, type: !89)
!881 = !DILocation(line: 644, column: 26, scope: !184)
!882 = !DILocation(line: 646, column: 11, scope: !184)
!883 = !DILocation(line: 646, column: 3, scope: !184)
!884 = !DILocation(line: 648, column: 5, scope: !885)
!885 = distinct !DILexicalBlock(scope: !184, file: !1, line: 646, column: 16)
!886 = !DILocation(line: 650, column: 5, scope: !885)
!887 = !DILocation(line: 651, column: 5, scope: !885)
!888 = !DILocation(line: 653, column: 17, scope: !184)
!889 = !DILocation(line: 653, column: 24, scope: !184)
!890 = !DILocation(line: 653, column: 10, scope: !184)
!891 = !DILocation(line: 653, column: 3, scope: !184)
!892 = !DILocation(line: 654, column: 1, scope: !184)
!893 = !DILocalVariable(name: "state", arg: 1, scope: !188, file: !1, line: 520, type: !77)
!894 = !DILocation(line: 520, column: 23, scope: !188)
!895 = !DILocalVariable(name: "tok", arg: 2, scope: !188, file: !1, line: 521, type: !72)
!896 = !DILocation(line: 521, column: 13, scope: !188)
!897 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !188, file: !1, line: 522, type: !86)
!898 = !DILocation(line: 522, column: 21, scope: !188)
!899 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !188, file: !1, line: 523, type: !86)
!900 = !DILocation(line: 523, column: 21, scope: !188)
!901 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !188, file: !1, line: 524, type: !89)
!902 = !DILocation(line: 524, column: 25, scope: !188)
!903 = !DILocation(line: 526, column: 11, scope: !188)
!904 = !DILocation(line: 526, column: 3, scope: !188)
!905 = !DILocation(line: 528, column: 5, scope: !906)
!906 = distinct !DILexicalBlock(scope: !188, file: !1, line: 526, column: 16)
!907 = !DILocation(line: 530, column: 5, scope: !906)
!908 = !DILocation(line: 530, column: 12, scope: !906)
!909 = !DILocation(line: 530, column: 20, scope: !906)
!910 = !DILocation(line: 531, column: 5, scope: !906)
!911 = !DILocation(line: 533, column: 17, scope: !188)
!912 = !DILocation(line: 533, column: 24, scope: !188)
!913 = !DILocation(line: 533, column: 10, scope: !188)
!914 = !DILocation(line: 533, column: 3, scope: !188)
!915 = !DILocation(line: 534, column: 1, scope: !188)
!916 = !DILocalVariable(name: "state", arg: 1, scope: !191, file: !1, line: 503, type: !77)
!917 = !DILocation(line: 503, column: 23, scope: !191)
!918 = !DILocalVariable(name: "tok", arg: 2, scope: !191, file: !1, line: 504, type: !72)
!919 = !DILocation(line: 504, column: 13, scope: !191)
!920 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !191, file: !1, line: 505, type: !86)
!921 = !DILocation(line: 505, column: 21, scope: !191)
!922 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !191, file: !1, line: 506, type: !86)
!923 = !DILocation(line: 506, column: 21, scope: !191)
!924 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !191, file: !1, line: 507, type: !89)
!925 = !DILocation(line: 507, column: 25, scope: !191)
!926 = !DILocation(line: 509, column: 11, scope: !191)
!927 = !DILocation(line: 509, column: 3, scope: !191)
!928 = !DILocation(line: 511, column: 5, scope: !929)
!929 = distinct !DILexicalBlock(scope: !191, file: !1, line: 509, column: 16)
!930 = !DILocation(line: 513, column: 5, scope: !929)
!931 = !DILocation(line: 513, column: 12, scope: !929)
!932 = !DILocation(line: 513, column: 20, scope: !929)
!933 = !DILocation(line: 514, column: 5, scope: !929)
!934 = !DILocation(line: 516, column: 17, scope: !191)
!935 = !DILocation(line: 516, column: 24, scope: !191)
!936 = !DILocation(line: 516, column: 10, scope: !191)
!937 = !DILocation(line: 516, column: 3, scope: !191)
!938 = !DILocation(line: 517, column: 1, scope: !191)
!939 = !DILocalVariable(name: "state", arg: 1, scope: !189, file: !1, line: 537, type: !77)
!940 = !DILocation(line: 537, column: 23, scope: !189)
!941 = !DILocalVariable(name: "tok", arg: 2, scope: !189, file: !1, line: 538, type: !72)
!942 = !DILocation(line: 538, column: 13, scope: !189)
!943 = !DILocalVariable(name: "ptr", arg: 3, scope: !189, file: !1, line: 539, type: !86)
!944 = !DILocation(line: 539, column: 21, scope: !189)
!945 = !DILocalVariable(name: "end", arg: 4, scope: !189, file: !1, line: 540, type: !86)
!946 = !DILocation(line: 540, column: 21, scope: !189)
!947 = !DILocalVariable(name: "enc", arg: 5, scope: !189, file: !1, line: 541, type: !89)
!948 = !DILocation(line: 541, column: 25, scope: !189)
!949 = !DILocation(line: 543, column: 11, scope: !189)
!950 = !DILocation(line: 543, column: 3, scope: !189)
!951 = !DILocation(line: 545, column: 5, scope: !952)
!952 = distinct !DILexicalBlock(scope: !189, file: !1, line: 543, column: 16)
!953 = !DILocation(line: 547, column: 5, scope: !952)
!954 = !DILocation(line: 548, column: 5, scope: !952)
!955 = !DILocation(line: 550, column: 9, scope: !956)
!956 = distinct !DILexicalBlock(scope: !952, file: !1, line: 550, column: 9)
!957 = !DILocation(line: 550, column: 9, scope: !952)
!958 = !DILocation(line: 551, column: 7, scope: !959)
!959 = distinct !DILexicalBlock(scope: !956, file: !1, line: 550, column: 55)
!960 = !DILocation(line: 551, column: 14, scope: !959)
!961 = !DILocation(line: 551, column: 22, scope: !959)
!962 = !DILocation(line: 552, column: 7, scope: !959)
!963 = !DILocation(line: 554, column: 5, scope: !952)
!964 = !DILocation(line: 556, column: 17, scope: !189)
!965 = !DILocation(line: 556, column: 24, scope: !189)
!966 = !DILocation(line: 556, column: 10, scope: !189)
!967 = !DILocation(line: 556, column: 3, scope: !189)
!968 = !DILocation(line: 557, column: 1, scope: !189)
!969 = !DILocalVariable(name: "state", arg: 1, scope: !190, file: !1, line: 560, type: !77)
!970 = !DILocation(line: 560, column: 23, scope: !190)
!971 = !DILocalVariable(name: "tok", arg: 2, scope: !190, file: !1, line: 561, type: !72)
!972 = !DILocation(line: 561, column: 13, scope: !190)
!973 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !190, file: !1, line: 562, type: !86)
!974 = !DILocation(line: 562, column: 21, scope: !190)
!975 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !190, file: !1, line: 563, type: !86)
!976 = !DILocation(line: 563, column: 21, scope: !190)
!977 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !190, file: !1, line: 564, type: !89)
!978 = !DILocation(line: 564, column: 25, scope: !190)
!979 = !DILocation(line: 566, column: 11, scope: !190)
!980 = !DILocation(line: 566, column: 3, scope: !190)
!981 = !DILocation(line: 568, column: 5, scope: !982)
!982 = distinct !DILexicalBlock(scope: !190, file: !1, line: 566, column: 16)
!983 = !DILocation(line: 570, column: 5, scope: !982)
!984 = !DILocation(line: 570, column: 12, scope: !982)
!985 = !DILocation(line: 570, column: 20, scope: !982)
!986 = !DILocation(line: 571, column: 5, scope: !982)
!987 = !DILocation(line: 571, column: 12, scope: !982)
!988 = !DILocation(line: 571, column: 22, scope: !982)
!989 = !DILocation(line: 572, column: 5, scope: !982)
!990 = !DILocation(line: 574, column: 17, scope: !190)
!991 = !DILocation(line: 574, column: 24, scope: !190)
!992 = !DILocation(line: 574, column: 10, scope: !190)
!993 = !DILocation(line: 574, column: 3, scope: !190)
!994 = !DILocation(line: 575, column: 1, scope: !190)
!995 = !DILocalVariable(name: "state", arg: 1, scope: !193, file: !1, line: 772, type: !77)
!996 = !DILocation(line: 772, column: 24, scope: !193)
!997 = !DILocalVariable(name: "tok", arg: 2, scope: !193, file: !1, line: 773, type: !72)
!998 = !DILocation(line: 773, column: 14, scope: !193)
!999 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !193, file: !1, line: 774, type: !86)
!1000 = !DILocation(line: 774, column: 22, scope: !193)
!1001 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !193, file: !1, line: 775, type: !86)
!1002 = !DILocation(line: 775, column: 22, scope: !193)
!1003 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !193, file: !1, line: 776, type: !89)
!1004 = !DILocation(line: 776, column: 26, scope: !193)
!1005 = !DILocation(line: 778, column: 11, scope: !193)
!1006 = !DILocation(line: 778, column: 3, scope: !193)
!1007 = !DILocation(line: 780, column: 5, scope: !1008)
!1008 = distinct !DILexicalBlock(scope: !193, file: !1, line: 778, column: 16)
!1009 = !DILocation(line: 782, column: 5, scope: !1008)
!1010 = !DILocation(line: 783, column: 5, scope: !1008)
!1011 = !DILocation(line: 786, column: 5, scope: !1008)
!1012 = !DILocation(line: 786, column: 12, scope: !1008)
!1013 = !DILocation(line: 786, column: 20, scope: !1008)
!1014 = !DILocation(line: 787, column: 5, scope: !1008)
!1015 = !DILocation(line: 789, column: 17, scope: !193)
!1016 = !DILocation(line: 789, column: 24, scope: !193)
!1017 = !DILocation(line: 789, column: 10, scope: !193)
!1018 = !DILocation(line: 789, column: 3, scope: !193)
!1019 = !DILocation(line: 790, column: 1, scope: !193)
!1020 = !DILocalVariable(name: "state", arg: 1, scope: !194, file: !1, line: 793, type: !77)
!1021 = !DILocation(line: 793, column: 24, scope: !194)
!1022 = !DILocalVariable(name: "tok", arg: 2, scope: !194, file: !1, line: 794, type: !72)
!1023 = !DILocation(line: 794, column: 14, scope: !194)
!1024 = !DILocalVariable(name: "ptr", arg: 3, scope: !194, file: !1, line: 795, type: !86)
!1025 = !DILocation(line: 795, column: 22, scope: !194)
!1026 = !DILocalVariable(name: "end", arg: 4, scope: !194, file: !1, line: 796, type: !86)
!1027 = !DILocation(line: 796, column: 22, scope: !194)
!1028 = !DILocalVariable(name: "enc", arg: 5, scope: !194, file: !1, line: 797, type: !89)
!1029 = !DILocation(line: 797, column: 26, scope: !194)
!1030 = !DILocation(line: 799, column: 11, scope: !194)
!1031 = !DILocation(line: 799, column: 3, scope: !194)
!1032 = !DILocation(line: 801, column: 5, scope: !1033)
!1033 = distinct !DILexicalBlock(scope: !194, file: !1, line: 799, column: 16)
!1034 = !DILocalVariable(name: "i", scope: !1035, file: !1, line: 814, type: !72)
!1035 = distinct !DILexicalBlock(scope: !1033, file: !1, line: 803, column: 5)
!1036 = !DILocation(line: 814, column: 11, scope: !1035)
!1037 = !DILocation(line: 815, column: 14, scope: !1038)
!1038 = distinct !DILexicalBlock(scope: !1035, file: !1, line: 815, column: 7)
!1039 = !DILocation(line: 815, column: 12, scope: !1038)
!1040 = !DILocation(line: 815, column: 19, scope: !1041)
!1041 = !DILexicalBlockFile(scope: !1042, file: !1, discriminator: 1)
!1042 = distinct !DILexicalBlock(scope: !1038, file: !1, line: 815, column: 7)
!1043 = !DILocation(line: 815, column: 21, scope: !1041)
!1044 = !DILocation(line: 815, column: 7, scope: !1041)
!1045 = !DILocation(line: 816, column: 13, scope: !1046)
!1046 = distinct !DILexicalBlock(scope: !1042, file: !1, line: 816, column: 13)
!1047 = !DILocation(line: 816, column: 13, scope: !1042)
!1048 = !DILocation(line: 817, column: 11, scope: !1049)
!1049 = distinct !DILexicalBlock(scope: !1046, file: !1, line: 816, column: 59)
!1050 = !DILocation(line: 817, column: 18, scope: !1049)
!1051 = !DILocation(line: 817, column: 26, scope: !1049)
!1052 = !DILocation(line: 818, column: 50, scope: !1049)
!1053 = !DILocation(line: 818, column: 48, scope: !1049)
!1054 = !DILocation(line: 818, column: 11, scope: !1049)
!1055 = !DILocation(line: 816, column: 13, scope: !1056)
!1056 = !DILexicalBlockFile(scope: !1046, file: !1, discriminator: 1)
!1057 = !DILocation(line: 815, column: 63, scope: !1058)
!1058 = !DILexicalBlockFile(scope: !1042, file: !1, discriminator: 2)
!1059 = !DILocation(line: 815, column: 7, scope: !1058)
!1060 = !DILocation(line: 821, column: 9, scope: !1061)
!1061 = distinct !DILexicalBlock(scope: !1033, file: !1, line: 821, column: 9)
!1062 = !DILocation(line: 821, column: 9, scope: !1033)
!1063 = !DILocation(line: 822, column: 7, scope: !1064)
!1064 = distinct !DILexicalBlock(scope: !1061, file: !1, line: 821, column: 58)
!1065 = !DILocation(line: 822, column: 14, scope: !1064)
!1066 = !DILocation(line: 822, column: 22, scope: !1064)
!1067 = !DILocation(line: 823, column: 7, scope: !1064)
!1068 = !DILocation(line: 825, column: 5, scope: !1033)
!1069 = !DILocation(line: 827, column: 5, scope: !1033)
!1070 = !DILocation(line: 827, column: 12, scope: !1033)
!1071 = !DILocation(line: 827, column: 20, scope: !1033)
!1072 = !DILocation(line: 828, column: 5, scope: !1033)
!1073 = !DILocation(line: 830, column: 17, scope: !194)
!1074 = !DILocation(line: 830, column: 24, scope: !194)
!1075 = !DILocation(line: 830, column: 10, scope: !194)
!1076 = !DILocation(line: 830, column: 3, scope: !194)
!1077 = !DILocation(line: 831, column: 1, scope: !194)
!1078 = !DILocalVariable(name: "state", arg: 1, scope: !195, file: !1, line: 928, type: !77)
!1079 = !DILocation(line: 928, column: 24, scope: !195)
!1080 = !DILocalVariable(name: "tok", arg: 2, scope: !195, file: !1, line: 929, type: !72)
!1081 = !DILocation(line: 929, column: 14, scope: !195)
!1082 = !DILocalVariable(name: "ptr", arg: 3, scope: !195, file: !1, line: 930, type: !86)
!1083 = !DILocation(line: 930, column: 22, scope: !195)
!1084 = !DILocalVariable(name: "end", arg: 4, scope: !195, file: !1, line: 931, type: !86)
!1085 = !DILocation(line: 931, column: 22, scope: !195)
!1086 = !DILocalVariable(name: "enc", arg: 5, scope: !195, file: !1, line: 932, type: !89)
!1087 = !DILocation(line: 932, column: 26, scope: !195)
!1088 = !DILocation(line: 934, column: 11, scope: !195)
!1089 = !DILocation(line: 934, column: 3, scope: !195)
!1090 = !DILocation(line: 936, column: 5, scope: !1091)
!1091 = distinct !DILexicalBlock(scope: !195, file: !1, line: 934, column: 16)
!1092 = !DILocation(line: 938, column: 9, scope: !1093)
!1093 = distinct !DILexicalBlock(scope: !1091, file: !1, line: 938, column: 9)
!1094 = !DILocation(line: 938, column: 9, scope: !1091)
!1095 = !DILocation(line: 942, column: 7, scope: !1096)
!1096 = distinct !DILexicalBlock(scope: !1093, file: !1, line: 941, column: 42)
!1097 = !DILocation(line: 942, column: 14, scope: !1096)
!1098 = !DILocation(line: 942, column: 22, scope: !1096)
!1099 = !DILocation(line: 943, column: 7, scope: !1096)
!1100 = !DILocation(line: 945, column: 9, scope: !1101)
!1101 = distinct !DILexicalBlock(scope: !1091, file: !1, line: 945, column: 9)
!1102 = !DILocation(line: 945, column: 9, scope: !1091)
!1103 = !DILocation(line: 949, column: 7, scope: !1104)
!1104 = distinct !DILexicalBlock(scope: !1101, file: !1, line: 948, column: 43)
!1105 = !DILocation(line: 949, column: 14, scope: !1104)
!1106 = !DILocation(line: 949, column: 22, scope: !1104)
!1107 = !DILocation(line: 950, column: 7, scope: !1104)
!1108 = !DILocation(line: 952, column: 9, scope: !1109)
!1109 = distinct !DILexicalBlock(scope: !1091, file: !1, line: 952, column: 9)
!1110 = !DILocation(line: 952, column: 9, scope: !1091)
!1111 = !DILocation(line: 956, column: 7, scope: !1112)
!1112 = distinct !DILexicalBlock(scope: !1109, file: !1, line: 955, column: 40)
!1113 = !DILocation(line: 956, column: 14, scope: !1112)
!1114 = !DILocation(line: 956, column: 22, scope: !1112)
!1115 = !DILocation(line: 957, column: 7, scope: !1112)
!1116 = !DILocation(line: 959, column: 5, scope: !1091)
!1117 = !DILocation(line: 961, column: 5, scope: !1091)
!1118 = !DILocation(line: 961, column: 12, scope: !1091)
!1119 = !DILocation(line: 961, column: 20, scope: !1091)
!1120 = !DILocation(line: 962, column: 5, scope: !1091)
!1121 = !DILocation(line: 964, column: 17, scope: !195)
!1122 = !DILocation(line: 964, column: 24, scope: !195)
!1123 = !DILocation(line: 964, column: 10, scope: !195)
!1124 = !DILocation(line: 964, column: 3, scope: !195)
!1125 = !DILocation(line: 965, column: 1, scope: !195)
!1126 = !DILocalVariable(name: "state", arg: 1, scope: !197, file: !1, line: 873, type: !77)
!1127 = !DILocation(line: 873, column: 24, scope: !197)
!1128 = !DILocalVariable(name: "tok", arg: 2, scope: !197, file: !1, line: 874, type: !72)
!1129 = !DILocation(line: 874, column: 14, scope: !197)
!1130 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !197, file: !1, line: 875, type: !86)
!1131 = !DILocation(line: 875, column: 22, scope: !197)
!1132 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !197, file: !1, line: 876, type: !86)
!1133 = !DILocation(line: 876, column: 22, scope: !197)
!1134 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !197, file: !1, line: 877, type: !89)
!1135 = !DILocation(line: 877, column: 26, scope: !197)
!1136 = !DILocation(line: 879, column: 11, scope: !197)
!1137 = !DILocation(line: 879, column: 3, scope: !197)
!1138 = !DILocation(line: 881, column: 5, scope: !1139)
!1139 = distinct !DILexicalBlock(scope: !197, file: !1, line: 879, column: 16)
!1140 = !DILocation(line: 883, column: 5, scope: !1139)
!1141 = !DILocation(line: 883, column: 12, scope: !1139)
!1142 = !DILocation(line: 883, column: 20, scope: !1139)
!1143 = !DILocation(line: 884, column: 5, scope: !1139)
!1144 = !DILocation(line: 886, column: 17, scope: !197)
!1145 = !DILocation(line: 886, column: 24, scope: !197)
!1146 = !DILocation(line: 886, column: 10, scope: !197)
!1147 = !DILocation(line: 886, column: 3, scope: !197)
!1148 = !DILocation(line: 887, column: 1, scope: !197)
!1149 = !DILocalVariable(name: "state", arg: 1, scope: !200, file: !1, line: 834, type: !77)
!1150 = !DILocation(line: 834, column: 24, scope: !200)
!1151 = !DILocalVariable(name: "tok", arg: 2, scope: !200, file: !1, line: 835, type: !72)
!1152 = !DILocation(line: 835, column: 14, scope: !200)
!1153 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !200, file: !1, line: 836, type: !86)
!1154 = !DILocation(line: 836, column: 22, scope: !200)
!1155 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !200, file: !1, line: 837, type: !86)
!1156 = !DILocation(line: 837, column: 22, scope: !200)
!1157 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !200, file: !1, line: 838, type: !89)
!1158 = !DILocation(line: 838, column: 26, scope: !200)
!1159 = !DILocation(line: 840, column: 11, scope: !200)
!1160 = !DILocation(line: 840, column: 3, scope: !200)
!1161 = !DILocation(line: 842, column: 5, scope: !1162)
!1162 = distinct !DILexicalBlock(scope: !200, file: !1, line: 840, column: 16)
!1163 = !DILocation(line: 846, column: 5, scope: !1162)
!1164 = !DILocation(line: 846, column: 12, scope: !1162)
!1165 = !DILocation(line: 846, column: 20, scope: !1162)
!1166 = !DILocation(line: 847, column: 5, scope: !1162)
!1167 = !DILocation(line: 849, column: 17, scope: !200)
!1168 = !DILocation(line: 849, column: 24, scope: !200)
!1169 = !DILocation(line: 849, column: 10, scope: !200)
!1170 = !DILocation(line: 849, column: 3, scope: !200)
!1171 = !DILocation(line: 850, column: 1, scope: !200)
!1172 = !DILocalVariable(name: "state", arg: 1, scope: !196, file: !1, line: 968, type: !77)
!1173 = !DILocation(line: 968, column: 24, scope: !196)
!1174 = !DILocalVariable(name: "tok", arg: 2, scope: !196, file: !1, line: 969, type: !72)
!1175 = !DILocation(line: 969, column: 14, scope: !196)
!1176 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !196, file: !1, line: 970, type: !86)
!1177 = !DILocation(line: 970, column: 22, scope: !196)
!1178 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !196, file: !1, line: 971, type: !86)
!1179 = !DILocation(line: 971, column: 22, scope: !196)
!1180 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !196, file: !1, line: 972, type: !89)
!1181 = !DILocation(line: 972, column: 26, scope: !196)
!1182 = !DILocation(line: 974, column: 11, scope: !196)
!1183 = !DILocation(line: 974, column: 3, scope: !196)
!1184 = !DILocation(line: 976, column: 5, scope: !1185)
!1185 = distinct !DILexicalBlock(scope: !196, file: !1, line: 974, column: 16)
!1186 = !DILocation(line: 978, column: 5, scope: !1185)
!1187 = !DILocation(line: 978, column: 12, scope: !1185)
!1188 = !DILocation(line: 978, column: 20, scope: !1185)
!1189 = !DILocation(line: 979, column: 5, scope: !1185)
!1190 = !DILocation(line: 981, column: 17, scope: !196)
!1191 = !DILocation(line: 981, column: 24, scope: !196)
!1192 = !DILocation(line: 981, column: 10, scope: !196)
!1193 = !DILocation(line: 981, column: 3, scope: !196)
!1194 = !DILocation(line: 982, column: 1, scope: !196)
!1195 = !DILocalVariable(name: "state", arg: 1, scope: !198, file: !1, line: 890, type: !77)
!1196 = !DILocation(line: 890, column: 24, scope: !198)
!1197 = !DILocalVariable(name: "tok", arg: 2, scope: !198, file: !1, line: 891, type: !72)
!1198 = !DILocation(line: 891, column: 14, scope: !198)
!1199 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !198, file: !1, line: 892, type: !86)
!1200 = !DILocation(line: 892, column: 22, scope: !198)
!1201 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !198, file: !1, line: 893, type: !86)
!1202 = !DILocation(line: 893, column: 22, scope: !198)
!1203 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !198, file: !1, line: 894, type: !89)
!1204 = !DILocation(line: 894, column: 26, scope: !198)
!1205 = !DILocation(line: 896, column: 11, scope: !198)
!1206 = !DILocation(line: 896, column: 3, scope: !198)
!1207 = !DILocation(line: 898, column: 5, scope: !1208)
!1208 = distinct !DILexicalBlock(scope: !198, file: !1, line: 896, column: 16)
!1209 = !DILocation(line: 900, column: 5, scope: !1208)
!1210 = !DILocation(line: 900, column: 12, scope: !1208)
!1211 = !DILocation(line: 900, column: 20, scope: !1208)
!1212 = !DILocation(line: 901, column: 5, scope: !1208)
!1213 = !DILocation(line: 903, column: 17, scope: !198)
!1214 = !DILocation(line: 903, column: 24, scope: !198)
!1215 = !DILocation(line: 903, column: 10, scope: !198)
!1216 = !DILocation(line: 903, column: 3, scope: !198)
!1217 = !DILocation(line: 904, column: 1, scope: !198)
!1218 = !DILocalVariable(name: "state", arg: 1, scope: !199, file: !1, line: 907, type: !77)
!1219 = !DILocation(line: 907, column: 24, scope: !199)
!1220 = !DILocalVariable(name: "tok", arg: 2, scope: !199, file: !1, line: 908, type: !72)
!1221 = !DILocation(line: 908, column: 14, scope: !199)
!1222 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !199, file: !1, line: 909, type: !86)
!1223 = !DILocation(line: 909, column: 22, scope: !199)
!1224 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !199, file: !1, line: 910, type: !86)
!1225 = !DILocation(line: 910, column: 22, scope: !199)
!1226 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !199, file: !1, line: 911, type: !89)
!1227 = !DILocation(line: 911, column: 26, scope: !199)
!1228 = !DILocation(line: 913, column: 11, scope: !199)
!1229 = !DILocation(line: 913, column: 3, scope: !199)
!1230 = !DILocation(line: 915, column: 5, scope: !1231)
!1231 = distinct !DILexicalBlock(scope: !199, file: !1, line: 913, column: 16)
!1232 = !DILocation(line: 917, column: 5, scope: !1231)
!1233 = !DILocation(line: 917, column: 12, scope: !1231)
!1234 = !DILocation(line: 917, column: 20, scope: !1231)
!1235 = !DILocation(line: 918, column: 5, scope: !1231)
!1236 = !DILocation(line: 920, column: 5, scope: !1231)
!1237 = !DILocation(line: 920, column: 12, scope: !1231)
!1238 = !DILocation(line: 920, column: 20, scope: !1231)
!1239 = !DILocation(line: 921, column: 5, scope: !1231)
!1240 = !DILocation(line: 923, column: 17, scope: !199)
!1241 = !DILocation(line: 923, column: 24, scope: !199)
!1242 = !DILocation(line: 923, column: 10, scope: !199)
!1243 = !DILocation(line: 923, column: 3, scope: !199)
!1244 = !DILocation(line: 924, column: 1, scope: !199)
!1245 = !DILocalVariable(name: "state", arg: 1, scope: !201, file: !1, line: 853, type: !77)
!1246 = !DILocation(line: 853, column: 24, scope: !201)
!1247 = !DILocalVariable(name: "tok", arg: 2, scope: !201, file: !1, line: 854, type: !72)
!1248 = !DILocation(line: 854, column: 14, scope: !201)
!1249 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !201, file: !1, line: 855, type: !86)
!1250 = !DILocation(line: 855, column: 22, scope: !201)
!1251 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !201, file: !1, line: 856, type: !86)
!1252 = !DILocation(line: 856, column: 22, scope: !201)
!1253 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !201, file: !1, line: 857, type: !89)
!1254 = !DILocation(line: 857, column: 26, scope: !201)
!1255 = !DILocation(line: 859, column: 11, scope: !201)
!1256 = !DILocation(line: 859, column: 3, scope: !201)
!1257 = !DILocation(line: 861, column: 5, scope: !1258)
!1258 = distinct !DILexicalBlock(scope: !201, file: !1, line: 859, column: 16)
!1259 = !DILocation(line: 863, column: 5, scope: !1258)
!1260 = !DILocation(line: 863, column: 12, scope: !1258)
!1261 = !DILocation(line: 863, column: 20, scope: !1258)
!1262 = !DILocation(line: 864, column: 5, scope: !1258)
!1263 = !DILocation(line: 866, column: 5, scope: !1258)
!1264 = !DILocation(line: 866, column: 12, scope: !1258)
!1265 = !DILocation(line: 866, column: 20, scope: !1258)
!1266 = !DILocation(line: 867, column: 5, scope: !1258)
!1267 = !DILocation(line: 869, column: 17, scope: !201)
!1268 = !DILocation(line: 869, column: 24, scope: !201)
!1269 = !DILocation(line: 869, column: 10, scope: !201)
!1270 = !DILocation(line: 869, column: 3, scope: !201)
!1271 = !DILocation(line: 870, column: 1, scope: !201)
!1272 = !DILocalVariable(name: "state", arg: 1, scope: !203, file: !1, line: 1003, type: !77)
!1273 = !DILocation(line: 1003, column: 24, scope: !203)
!1274 = !DILocalVariable(name: "tok", arg: 2, scope: !203, file: !1, line: 1004, type: !72)
!1275 = !DILocation(line: 1004, column: 14, scope: !203)
!1276 = !DILocalVariable(name: "ptr", arg: 3, scope: !203, file: !1, line: 1005, type: !86)
!1277 = !DILocation(line: 1005, column: 22, scope: !203)
!1278 = !DILocalVariable(name: "end", arg: 4, scope: !203, file: !1, line: 1006, type: !86)
!1279 = !DILocation(line: 1006, column: 22, scope: !203)
!1280 = !DILocalVariable(name: "enc", arg: 5, scope: !203, file: !1, line: 1007, type: !89)
!1281 = !DILocation(line: 1007, column: 26, scope: !203)
!1282 = !DILocation(line: 1009, column: 11, scope: !203)
!1283 = !DILocation(line: 1009, column: 3, scope: !203)
!1284 = !DILocation(line: 1011, column: 5, scope: !1285)
!1285 = distinct !DILexicalBlock(scope: !203, file: !1, line: 1009, column: 16)
!1286 = !DILocation(line: 1013, column: 9, scope: !1287)
!1287 = distinct !DILexicalBlock(scope: !1285, file: !1, line: 1013, column: 9)
!1288 = !DILocation(line: 1013, column: 9, scope: !1285)
!1289 = !DILocation(line: 1014, column: 7, scope: !1290)
!1290 = distinct !DILexicalBlock(scope: !1287, file: !1, line: 1013, column: 55)
!1291 = !DILocation(line: 1014, column: 14, scope: !1290)
!1292 = !DILocation(line: 1014, column: 22, scope: !1290)
!1293 = !DILocation(line: 1015, column: 7, scope: !1290)
!1294 = !DILocation(line: 1015, column: 14, scope: !1290)
!1295 = !DILocation(line: 1015, column: 24, scope: !1290)
!1296 = !DILocation(line: 1016, column: 7, scope: !1290)
!1297 = !DILocation(line: 1018, column: 9, scope: !1298)
!1298 = distinct !DILexicalBlock(scope: !1285, file: !1, line: 1018, column: 9)
!1299 = !DILocation(line: 1018, column: 9, scope: !1285)
!1300 = !DILocation(line: 1019, column: 7, scope: !1301)
!1301 = distinct !DILexicalBlock(scope: !1298, file: !1, line: 1018, column: 53)
!1302 = !DILocation(line: 1019, column: 14, scope: !1301)
!1303 = !DILocation(line: 1019, column: 22, scope: !1301)
!1304 = !DILocation(line: 1020, column: 7, scope: !1301)
!1305 = !DILocation(line: 1020, column: 14, scope: !1301)
!1306 = !DILocation(line: 1020, column: 24, scope: !1301)
!1307 = !DILocation(line: 1021, column: 7, scope: !1301)
!1308 = !DILocation(line: 1023, column: 5, scope: !1285)
!1309 = !DILocation(line: 1025, column: 5, scope: !1285)
!1310 = !DILocation(line: 1025, column: 12, scope: !1285)
!1311 = !DILocation(line: 1025, column: 20, scope: !1285)
!1312 = !DILocation(line: 1026, column: 5, scope: !1285)
!1313 = !DILocation(line: 1026, column: 12, scope: !1285)
!1314 = !DILocation(line: 1026, column: 18, scope: !1285)
!1315 = !DILocation(line: 1027, column: 5, scope: !1285)
!1316 = !DILocation(line: 1029, column: 17, scope: !203)
!1317 = !DILocation(line: 1029, column: 24, scope: !203)
!1318 = !DILocation(line: 1029, column: 10, scope: !203)
!1319 = !DILocation(line: 1029, column: 3, scope: !203)
!1320 = !DILocation(line: 1030, column: 1, scope: !203)
!1321 = !DILocalVariable(name: "state", arg: 1, scope: !204, file: !1, line: 1033, type: !77)
!1322 = !DILocation(line: 1033, column: 24, scope: !204)
!1323 = !DILocalVariable(name: "tok", arg: 2, scope: !204, file: !1, line: 1034, type: !72)
!1324 = !DILocation(line: 1034, column: 14, scope: !204)
!1325 = !DILocalVariable(name: "ptr", arg: 3, scope: !204, file: !1, line: 1035, type: !86)
!1326 = !DILocation(line: 1035, column: 22, scope: !204)
!1327 = !DILocalVariable(name: "end", arg: 4, scope: !204, file: !1, line: 1036, type: !86)
!1328 = !DILocation(line: 1036, column: 22, scope: !204)
!1329 = !DILocalVariable(name: "enc", arg: 5, scope: !204, file: !1, line: 1037, type: !89)
!1330 = !DILocation(line: 1037, column: 26, scope: !204)
!1331 = !DILocation(line: 1039, column: 11, scope: !204)
!1332 = !DILocation(line: 1039, column: 3, scope: !204)
!1333 = !DILocation(line: 1041, column: 5, scope: !1334)
!1334 = distinct !DILexicalBlock(scope: !204, file: !1, line: 1039, column: 16)
!1335 = !DILocation(line: 1043, column: 9, scope: !1336)
!1336 = distinct !DILexicalBlock(scope: !1334, file: !1, line: 1043, column: 9)
!1337 = !DILocation(line: 1043, column: 9, scope: !1334)
!1338 = !DILocation(line: 1047, column: 7, scope: !1339)
!1339 = distinct !DILexicalBlock(scope: !1336, file: !1, line: 1046, column: 41)
!1340 = !DILocation(line: 1047, column: 14, scope: !1339)
!1341 = !DILocation(line: 1047, column: 22, scope: !1339)
!1342 = !DILocation(line: 1048, column: 7, scope: !1339)
!1343 = !DILocation(line: 1050, column: 5, scope: !1334)
!1344 = !DILocation(line: 1052, column: 5, scope: !1334)
!1345 = !DILocation(line: 1052, column: 12, scope: !1334)
!1346 = !DILocation(line: 1052, column: 18, scope: !1334)
!1347 = !DILocation(line: 1053, column: 5, scope: !1334)
!1348 = !DILocation(line: 1053, column: 12, scope: !1334)
!1349 = !DILocation(line: 1053, column: 20, scope: !1334)
!1350 = !DILocation(line: 1054, column: 5, scope: !1334)
!1351 = !DILocation(line: 1057, column: 5, scope: !1334)
!1352 = !DILocation(line: 1057, column: 12, scope: !1334)
!1353 = !DILocation(line: 1057, column: 20, scope: !1334)
!1354 = !DILocation(line: 1058, column: 5, scope: !1334)
!1355 = !DILocation(line: 1060, column: 5, scope: !1334)
!1356 = !DILocation(line: 1060, column: 12, scope: !1334)
!1357 = !DILocation(line: 1060, column: 20, scope: !1334)
!1358 = !DILocation(line: 1061, column: 5, scope: !1334)
!1359 = !DILocation(line: 1063, column: 5, scope: !1334)
!1360 = !DILocation(line: 1063, column: 12, scope: !1334)
!1361 = !DILocation(line: 1063, column: 20, scope: !1334)
!1362 = !DILocation(line: 1064, column: 5, scope: !1334)
!1363 = !DILocation(line: 1066, column: 5, scope: !1334)
!1364 = !DILocation(line: 1066, column: 12, scope: !1334)
!1365 = !DILocation(line: 1066, column: 20, scope: !1334)
!1366 = !DILocation(line: 1067, column: 5, scope: !1334)
!1367 = !DILocation(line: 1069, column: 17, scope: !204)
!1368 = !DILocation(line: 1069, column: 24, scope: !204)
!1369 = !DILocation(line: 1069, column: 10, scope: !204)
!1370 = !DILocation(line: 1069, column: 3, scope: !204)
!1371 = !DILocation(line: 1070, column: 1, scope: !204)
!1372 = !DILocalVariable(name: "state", arg: 1, scope: !205, file: !1, line: 1073, type: !77)
!1373 = !DILocation(line: 1073, column: 24, scope: !205)
!1374 = !DILocalVariable(name: "tok", arg: 2, scope: !205, file: !1, line: 1074, type: !72)
!1375 = !DILocation(line: 1074, column: 14, scope: !205)
!1376 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !205, file: !1, line: 1075, type: !86)
!1377 = !DILocation(line: 1075, column: 22, scope: !205)
!1378 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !205, file: !1, line: 1076, type: !86)
!1379 = !DILocation(line: 1076, column: 22, scope: !205)
!1380 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !205, file: !1, line: 1077, type: !89)
!1381 = !DILocation(line: 1077, column: 26, scope: !205)
!1382 = !DILocation(line: 1079, column: 11, scope: !205)
!1383 = !DILocation(line: 1079, column: 3, scope: !205)
!1384 = !DILocation(line: 1081, column: 5, scope: !1385)
!1385 = distinct !DILexicalBlock(scope: !205, file: !1, line: 1079, column: 16)
!1386 = !DILocation(line: 1083, column: 5, scope: !1385)
!1387 = !DILocation(line: 1083, column: 12, scope: !1385)
!1388 = !DILocation(line: 1083, column: 20, scope: !1385)
!1389 = !DILocation(line: 1084, column: 5, scope: !1385)
!1390 = !DILocation(line: 1084, column: 12, scope: !1385)
!1391 = !DILocation(line: 1084, column: 22, scope: !1385)
!1392 = !DILocation(line: 1085, column: 5, scope: !1385)
!1393 = !DILocation(line: 1087, column: 5, scope: !1385)
!1394 = !DILocation(line: 1087, column: 12, scope: !1385)
!1395 = !DILocation(line: 1087, column: 20, scope: !1385)
!1396 = !DILocation(line: 1088, column: 5, scope: !1385)
!1397 = !DILocation(line: 1088, column: 12, scope: !1385)
!1398 = !DILocation(line: 1088, column: 22, scope: !1385)
!1399 = !DILocation(line: 1089, column: 5, scope: !1385)
!1400 = !DILocation(line: 1091, column: 5, scope: !1385)
!1401 = !DILocation(line: 1091, column: 12, scope: !1385)
!1402 = !DILocation(line: 1091, column: 20, scope: !1385)
!1403 = !DILocation(line: 1092, column: 5, scope: !1385)
!1404 = !DILocation(line: 1094, column: 17, scope: !205)
!1405 = !DILocation(line: 1094, column: 24, scope: !205)
!1406 = !DILocation(line: 1094, column: 10, scope: !205)
!1407 = !DILocation(line: 1094, column: 3, scope: !205)
!1408 = !DILocation(line: 1095, column: 1, scope: !205)
!1409 = !DILocalVariable(name: "state", arg: 1, scope: !208, file: !1, line: 1137, type: !77)
!1410 = !DILocation(line: 1137, column: 24, scope: !208)
!1411 = !DILocalVariable(name: "tok", arg: 2, scope: !208, file: !1, line: 1138, type: !72)
!1412 = !DILocation(line: 1138, column: 14, scope: !208)
!1413 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !208, file: !1, line: 1139, type: !86)
!1414 = !DILocation(line: 1139, column: 22, scope: !208)
!1415 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !208, file: !1, line: 1140, type: !86)
!1416 = !DILocation(line: 1140, column: 22, scope: !208)
!1417 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !208, file: !1, line: 1141, type: !89)
!1418 = !DILocation(line: 1141, column: 26, scope: !208)
!1419 = !DILocation(line: 1143, column: 11, scope: !208)
!1420 = !DILocation(line: 1143, column: 3, scope: !208)
!1421 = !DILocation(line: 1145, column: 5, scope: !1422)
!1422 = distinct !DILexicalBlock(scope: !208, file: !1, line: 1143, column: 16)
!1423 = !DILocation(line: 1147, column: 5, scope: !1422)
!1424 = !DILocation(line: 1147, column: 12, scope: !1422)
!1425 = !DILocation(line: 1147, column: 18, scope: !1422)
!1426 = !DILocation(line: 1148, column: 5, scope: !1422)
!1427 = !DILocation(line: 1151, column: 5, scope: !1422)
!1428 = !DILocation(line: 1151, column: 12, scope: !1422)
!1429 = !DILocation(line: 1151, column: 20, scope: !1422)
!1430 = !DILocation(line: 1152, column: 5, scope: !1422)
!1431 = !DILocation(line: 1154, column: 5, scope: !1422)
!1432 = !DILocation(line: 1154, column: 12, scope: !1422)
!1433 = !DILocation(line: 1154, column: 20, scope: !1422)
!1434 = !DILocation(line: 1155, column: 5, scope: !1422)
!1435 = !DILocation(line: 1157, column: 5, scope: !1422)
!1436 = !DILocation(line: 1157, column: 12, scope: !1422)
!1437 = !DILocation(line: 1157, column: 20, scope: !1422)
!1438 = !DILocation(line: 1158, column: 5, scope: !1422)
!1439 = !DILocation(line: 1160, column: 5, scope: !1422)
!1440 = !DILocation(line: 1160, column: 12, scope: !1422)
!1441 = !DILocation(line: 1160, column: 20, scope: !1422)
!1442 = !DILocation(line: 1161, column: 5, scope: !1422)
!1443 = !DILocation(line: 1163, column: 17, scope: !208)
!1444 = !DILocation(line: 1163, column: 24, scope: !208)
!1445 = !DILocation(line: 1163, column: 10, scope: !208)
!1446 = !DILocation(line: 1163, column: 3, scope: !208)
!1447 = !DILocation(line: 1164, column: 1, scope: !208)
!1448 = !DILocalVariable(name: "state", arg: 1, scope: !209, file: !1, line: 1167, type: !77)
!1449 = !DILocation(line: 1167, column: 24, scope: !209)
!1450 = !DILocalVariable(name: "tok", arg: 2, scope: !209, file: !1, line: 1168, type: !72)
!1451 = !DILocation(line: 1168, column: 14, scope: !209)
!1452 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !209, file: !1, line: 1169, type: !86)
!1453 = !DILocation(line: 1169, column: 22, scope: !209)
!1454 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !209, file: !1, line: 1170, type: !86)
!1455 = !DILocation(line: 1170, column: 22, scope: !209)
!1456 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !209, file: !1, line: 1171, type: !89)
!1457 = !DILocation(line: 1171, column: 26, scope: !209)
!1458 = !DILocation(line: 1173, column: 11, scope: !209)
!1459 = !DILocation(line: 1173, column: 3, scope: !209)
!1460 = !DILocation(line: 1175, column: 5, scope: !1461)
!1461 = distinct !DILexicalBlock(scope: !209, file: !1, line: 1173, column: 16)
!1462 = !DILocation(line: 1177, column: 5, scope: !1461)
!1463 = !DILocation(line: 1177, column: 12, scope: !1461)
!1464 = !DILocation(line: 1177, column: 18, scope: !1461)
!1465 = !DILocation(line: 1178, column: 9, scope: !1466)
!1466 = distinct !DILexicalBlock(scope: !1461, file: !1, line: 1178, column: 9)
!1467 = !DILocation(line: 1178, column: 16, scope: !1466)
!1468 = !DILocation(line: 1178, column: 22, scope: !1466)
!1469 = !DILocation(line: 1178, column: 9, scope: !1461)
!1470 = !DILocation(line: 1179, column: 7, scope: !1471)
!1471 = distinct !DILexicalBlock(scope: !1466, file: !1, line: 1178, column: 28)
!1472 = !DILocation(line: 1179, column: 14, scope: !1471)
!1473 = !DILocation(line: 1179, column: 22, scope: !1471)
!1474 = !DILocation(line: 1180, column: 7, scope: !1471)
!1475 = !DILocation(line: 1180, column: 14, scope: !1471)
!1476 = !DILocation(line: 1180, column: 24, scope: !1471)
!1477 = !DILocation(line: 1181, column: 5, scope: !1471)
!1478 = !DILocation(line: 1182, column: 5, scope: !1461)
!1479 = !DILocation(line: 1184, column: 5, scope: !1461)
!1480 = !DILocation(line: 1184, column: 12, scope: !1461)
!1481 = !DILocation(line: 1184, column: 18, scope: !1461)
!1482 = !DILocation(line: 1185, column: 9, scope: !1483)
!1483 = distinct !DILexicalBlock(scope: !1461, file: !1, line: 1185, column: 9)
!1484 = !DILocation(line: 1185, column: 16, scope: !1483)
!1485 = !DILocation(line: 1185, column: 22, scope: !1483)
!1486 = !DILocation(line: 1185, column: 9, scope: !1461)
!1487 = !DILocation(line: 1186, column: 7, scope: !1488)
!1488 = distinct !DILexicalBlock(scope: !1483, file: !1, line: 1185, column: 28)
!1489 = !DILocation(line: 1186, column: 14, scope: !1488)
!1490 = !DILocation(line: 1186, column: 22, scope: !1488)
!1491 = !DILocation(line: 1187, column: 7, scope: !1488)
!1492 = !DILocation(line: 1187, column: 14, scope: !1488)
!1493 = !DILocation(line: 1187, column: 24, scope: !1488)
!1494 = !DILocation(line: 1188, column: 5, scope: !1488)
!1495 = !DILocation(line: 1189, column: 5, scope: !1461)
!1496 = !DILocation(line: 1191, column: 5, scope: !1461)
!1497 = !DILocation(line: 1191, column: 12, scope: !1461)
!1498 = !DILocation(line: 1191, column: 18, scope: !1461)
!1499 = !DILocation(line: 1192, column: 9, scope: !1500)
!1500 = distinct !DILexicalBlock(scope: !1461, file: !1, line: 1192, column: 9)
!1501 = !DILocation(line: 1192, column: 16, scope: !1500)
!1502 = !DILocation(line: 1192, column: 22, scope: !1500)
!1503 = !DILocation(line: 1192, column: 9, scope: !1461)
!1504 = !DILocation(line: 1193, column: 7, scope: !1505)
!1505 = distinct !DILexicalBlock(scope: !1500, file: !1, line: 1192, column: 28)
!1506 = !DILocation(line: 1193, column: 14, scope: !1505)
!1507 = !DILocation(line: 1193, column: 22, scope: !1505)
!1508 = !DILocation(line: 1194, column: 7, scope: !1505)
!1509 = !DILocation(line: 1194, column: 14, scope: !1505)
!1510 = !DILocation(line: 1194, column: 24, scope: !1505)
!1511 = !DILocation(line: 1195, column: 5, scope: !1505)
!1512 = !DILocation(line: 1196, column: 5, scope: !1461)
!1513 = !DILocation(line: 1198, column: 5, scope: !1461)
!1514 = !DILocation(line: 1198, column: 12, scope: !1461)
!1515 = !DILocation(line: 1198, column: 18, scope: !1461)
!1516 = !DILocation(line: 1199, column: 9, scope: !1517)
!1517 = distinct !DILexicalBlock(scope: !1461, file: !1, line: 1199, column: 9)
!1518 = !DILocation(line: 1199, column: 16, scope: !1517)
!1519 = !DILocation(line: 1199, column: 22, scope: !1517)
!1520 = !DILocation(line: 1199, column: 9, scope: !1461)
!1521 = !DILocation(line: 1200, column: 7, scope: !1522)
!1522 = distinct !DILexicalBlock(scope: !1517, file: !1, line: 1199, column: 28)
!1523 = !DILocation(line: 1200, column: 14, scope: !1522)
!1524 = !DILocation(line: 1200, column: 22, scope: !1522)
!1525 = !DILocation(line: 1201, column: 7, scope: !1522)
!1526 = !DILocation(line: 1201, column: 14, scope: !1522)
!1527 = !DILocation(line: 1201, column: 24, scope: !1522)
!1528 = !DILocation(line: 1202, column: 5, scope: !1522)
!1529 = !DILocation(line: 1203, column: 5, scope: !1461)
!1530 = !DILocation(line: 1205, column: 5, scope: !1461)
!1531 = !DILocation(line: 1205, column: 12, scope: !1461)
!1532 = !DILocation(line: 1205, column: 20, scope: !1461)
!1533 = !DILocation(line: 1206, column: 5, scope: !1461)
!1534 = !DILocation(line: 1208, column: 5, scope: !1461)
!1535 = !DILocation(line: 1208, column: 12, scope: !1461)
!1536 = !DILocation(line: 1208, column: 20, scope: !1461)
!1537 = !DILocation(line: 1209, column: 5, scope: !1461)
!1538 = !DILocation(line: 1211, column: 17, scope: !209)
!1539 = !DILocation(line: 1211, column: 24, scope: !209)
!1540 = !DILocation(line: 1211, column: 10, scope: !209)
!1541 = !DILocation(line: 1211, column: 3, scope: !209)
!1542 = !DILocation(line: 1212, column: 1, scope: !209)
!1543 = !DILocalVariable(name: "state", arg: 1, scope: !206, file: !1, line: 1098, type: !77)
!1544 = !DILocation(line: 1098, column: 24, scope: !206)
!1545 = !DILocalVariable(name: "tok", arg: 2, scope: !206, file: !1, line: 1099, type: !72)
!1546 = !DILocation(line: 1099, column: 14, scope: !206)
!1547 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !206, file: !1, line: 1100, type: !86)
!1548 = !DILocation(line: 1100, column: 22, scope: !206)
!1549 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !206, file: !1, line: 1101, type: !86)
!1550 = !DILocation(line: 1101, column: 22, scope: !206)
!1551 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !206, file: !1, line: 1102, type: !89)
!1552 = !DILocation(line: 1102, column: 26, scope: !206)
!1553 = !DILocation(line: 1104, column: 11, scope: !206)
!1554 = !DILocation(line: 1104, column: 3, scope: !206)
!1555 = !DILocation(line: 1106, column: 5, scope: !1556)
!1556 = distinct !DILexicalBlock(scope: !206, file: !1, line: 1104, column: 16)
!1557 = !DILocation(line: 1109, column: 5, scope: !1556)
!1558 = !DILocation(line: 1109, column: 12, scope: !1556)
!1559 = !DILocation(line: 1109, column: 20, scope: !1556)
!1560 = !DILocation(line: 1110, column: 5, scope: !1556)
!1561 = !DILocation(line: 1112, column: 17, scope: !206)
!1562 = !DILocation(line: 1112, column: 24, scope: !206)
!1563 = !DILocation(line: 1112, column: 10, scope: !206)
!1564 = !DILocation(line: 1112, column: 3, scope: !206)
!1565 = !DILocation(line: 1113, column: 1, scope: !206)
!1566 = !DILocalVariable(name: "state", arg: 1, scope: !207, file: !1, line: 1116, type: !77)
!1567 = !DILocation(line: 1116, column: 24, scope: !207)
!1568 = !DILocalVariable(name: "tok", arg: 2, scope: !207, file: !1, line: 1117, type: !72)
!1569 = !DILocation(line: 1117, column: 14, scope: !207)
!1570 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !207, file: !1, line: 1118, type: !86)
!1571 = !DILocation(line: 1118, column: 22, scope: !207)
!1572 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !207, file: !1, line: 1119, type: !86)
!1573 = !DILocation(line: 1119, column: 22, scope: !207)
!1574 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !207, file: !1, line: 1120, type: !89)
!1575 = !DILocation(line: 1120, column: 26, scope: !207)
!1576 = !DILocation(line: 1122, column: 11, scope: !207)
!1577 = !DILocation(line: 1122, column: 3, scope: !207)
!1578 = !DILocation(line: 1124, column: 5, scope: !1579)
!1579 = distinct !DILexicalBlock(scope: !207, file: !1, line: 1122, column: 16)
!1580 = !DILocation(line: 1126, column: 5, scope: !1579)
!1581 = !DILocation(line: 1126, column: 12, scope: !1579)
!1582 = !DILocation(line: 1126, column: 20, scope: !1579)
!1583 = !DILocation(line: 1127, column: 5, scope: !1579)
!1584 = !DILocation(line: 1127, column: 12, scope: !1579)
!1585 = !DILocation(line: 1127, column: 22, scope: !1579)
!1586 = !DILocation(line: 1128, column: 5, scope: !1579)
!1587 = !DILocation(line: 1130, column: 5, scope: !1579)
!1588 = !DILocation(line: 1130, column: 12, scope: !1579)
!1589 = !DILocation(line: 1130, column: 20, scope: !1579)
!1590 = !DILocation(line: 1131, column: 5, scope: !1579)
!1591 = !DILocation(line: 1133, column: 17, scope: !207)
!1592 = !DILocation(line: 1133, column: 24, scope: !207)
!1593 = !DILocation(line: 1133, column: 10, scope: !207)
!1594 = !DILocation(line: 1133, column: 3, scope: !207)
!1595 = !DILocation(line: 1134, column: 1, scope: !207)
!1596 = !DILocalVariable(name: "state", arg: 1, scope: !211, file: !1, line: 674, type: !77)
!1597 = !DILocation(line: 674, column: 25, scope: !211)
!1598 = !DILocalVariable(name: "tok", arg: 2, scope: !211, file: !1, line: 675, type: !72)
!1599 = !DILocation(line: 675, column: 15, scope: !211)
!1600 = !DILocalVariable(name: "ptr", arg: 3, scope: !211, file: !1, line: 676, type: !86)
!1601 = !DILocation(line: 676, column: 23, scope: !211)
!1602 = !DILocalVariable(name: "end", arg: 4, scope: !211, file: !1, line: 677, type: !86)
!1603 = !DILocation(line: 677, column: 23, scope: !211)
!1604 = !DILocalVariable(name: "enc", arg: 5, scope: !211, file: !1, line: 678, type: !89)
!1605 = !DILocation(line: 678, column: 27, scope: !211)
!1606 = !DILocation(line: 680, column: 11, scope: !211)
!1607 = !DILocation(line: 680, column: 3, scope: !211)
!1608 = !DILocation(line: 682, column: 5, scope: !1609)
!1609 = distinct !DILexicalBlock(scope: !211, file: !1, line: 680, column: 16)
!1610 = !DILocation(line: 684, column: 9, scope: !1611)
!1611 = distinct !DILexicalBlock(scope: !1609, file: !1, line: 684, column: 9)
!1612 = !DILocation(line: 684, column: 9, scope: !1609)
!1613 = !DILocation(line: 685, column: 7, scope: !1614)
!1614 = distinct !DILexicalBlock(scope: !1611, file: !1, line: 684, column: 56)
!1615 = !DILocation(line: 685, column: 14, scope: !1614)
!1616 = !DILocation(line: 685, column: 22, scope: !1614)
!1617 = !DILocation(line: 686, column: 7, scope: !1614)
!1618 = !DILocation(line: 688, column: 9, scope: !1619)
!1619 = distinct !DILexicalBlock(scope: !1609, file: !1, line: 688, column: 9)
!1620 = !DILocation(line: 688, column: 9, scope: !1609)
!1621 = !DILocation(line: 689, column: 7, scope: !1622)
!1622 = distinct !DILexicalBlock(scope: !1619, file: !1, line: 688, column: 56)
!1623 = !DILocation(line: 689, column: 14, scope: !1622)
!1624 = !DILocation(line: 689, column: 22, scope: !1622)
!1625 = !DILocation(line: 690, column: 7, scope: !1622)
!1626 = !DILocation(line: 692, column: 5, scope: !1609)
!1627 = !DILocation(line: 694, column: 17, scope: !211)
!1628 = !DILocation(line: 694, column: 24, scope: !211)
!1629 = !DILocation(line: 694, column: 10, scope: !211)
!1630 = !DILocation(line: 694, column: 3, scope: !211)
!1631 = !DILocation(line: 695, column: 1, scope: !211)
!1632 = !DILocalVariable(name: "state", arg: 1, scope: !212, file: !1, line: 715, type: !77)
!1633 = !DILocation(line: 715, column: 25, scope: !212)
!1634 = !DILocalVariable(name: "tok", arg: 2, scope: !212, file: !1, line: 716, type: !72)
!1635 = !DILocation(line: 716, column: 15, scope: !212)
!1636 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !212, file: !1, line: 717, type: !86)
!1637 = !DILocation(line: 717, column: 23, scope: !212)
!1638 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !212, file: !1, line: 718, type: !86)
!1639 = !DILocation(line: 718, column: 23, scope: !212)
!1640 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !212, file: !1, line: 719, type: !89)
!1641 = !DILocation(line: 719, column: 27, scope: !212)
!1642 = !DILocation(line: 721, column: 11, scope: !212)
!1643 = !DILocation(line: 721, column: 3, scope: !212)
!1644 = !DILocation(line: 723, column: 5, scope: !1645)
!1645 = distinct !DILexicalBlock(scope: !212, file: !1, line: 721, column: 16)
!1646 = !DILocation(line: 725, column: 5, scope: !1645)
!1647 = !DILocation(line: 725, column: 12, scope: !1645)
!1648 = !DILocation(line: 725, column: 20, scope: !1645)
!1649 = !DILocation(line: 726, column: 5, scope: !1645)
!1650 = !DILocation(line: 726, column: 12, scope: !1645)
!1651 = !DILocation(line: 726, column: 22, scope: !1645)
!1652 = !DILocation(line: 727, column: 5, scope: !1645)
!1653 = !DILocation(line: 729, column: 17, scope: !212)
!1654 = !DILocation(line: 729, column: 24, scope: !212)
!1655 = !DILocation(line: 729, column: 10, scope: !212)
!1656 = !DILocation(line: 729, column: 3, scope: !212)
!1657 = !DILocation(line: 730, column: 1, scope: !212)
!1658 = !DILocalVariable(name: "state", arg: 1, scope: !213, file: !1, line: 698, type: !77)
!1659 = !DILocation(line: 698, column: 25, scope: !213)
!1660 = !DILocalVariable(name: "tok", arg: 2, scope: !213, file: !1, line: 699, type: !72)
!1661 = !DILocation(line: 699, column: 15, scope: !213)
!1662 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !213, file: !1, line: 700, type: !86)
!1663 = !DILocation(line: 700, column: 23, scope: !213)
!1664 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !213, file: !1, line: 701, type: !86)
!1665 = !DILocation(line: 701, column: 23, scope: !213)
!1666 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !213, file: !1, line: 702, type: !89)
!1667 = !DILocation(line: 702, column: 27, scope: !213)
!1668 = !DILocation(line: 704, column: 11, scope: !213)
!1669 = !DILocation(line: 704, column: 3, scope: !213)
!1670 = !DILocation(line: 706, column: 5, scope: !1671)
!1671 = distinct !DILexicalBlock(scope: !213, file: !1, line: 704, column: 16)
!1672 = !DILocation(line: 708, column: 5, scope: !1671)
!1673 = !DILocation(line: 708, column: 12, scope: !1671)
!1674 = !DILocation(line: 708, column: 20, scope: !1671)
!1675 = !DILocation(line: 709, column: 5, scope: !1671)
!1676 = !DILocation(line: 711, column: 17, scope: !213)
!1677 = !DILocation(line: 711, column: 24, scope: !213)
!1678 = !DILocation(line: 711, column: 10, scope: !213)
!1679 = !DILocation(line: 711, column: 3, scope: !213)
!1680 = !DILocation(line: 712, column: 1, scope: !213)
!1681 = !DILocalVariable(name: "state", arg: 1, scope: !214, file: !1, line: 733, type: !77)
!1682 = !DILocation(line: 733, column: 25, scope: !214)
!1683 = !DILocalVariable(name: "tok", arg: 2, scope: !214, file: !1, line: 734, type: !72)
!1684 = !DILocation(line: 734, column: 15, scope: !214)
!1685 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !214, file: !1, line: 735, type: !86)
!1686 = !DILocation(line: 735, column: 23, scope: !214)
!1687 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !214, file: !1, line: 736, type: !86)
!1688 = !DILocation(line: 736, column: 23, scope: !214)
!1689 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !214, file: !1, line: 737, type: !89)
!1690 = !DILocation(line: 737, column: 27, scope: !214)
!1691 = !DILocation(line: 739, column: 11, scope: !214)
!1692 = !DILocation(line: 739, column: 3, scope: !214)
!1693 = !DILocation(line: 741, column: 5, scope: !1694)
!1694 = distinct !DILexicalBlock(scope: !214, file: !1, line: 739, column: 16)
!1695 = !DILocation(line: 743, column: 5, scope: !1694)
!1696 = !DILocation(line: 743, column: 12, scope: !1694)
!1697 = !DILocation(line: 743, column: 20, scope: !1694)
!1698 = !DILocation(line: 744, column: 5, scope: !1694)
!1699 = !DILocation(line: 744, column: 12, scope: !1694)
!1700 = !DILocation(line: 744, column: 22, scope: !1694)
!1701 = !DILocation(line: 745, column: 5, scope: !1694)
!1702 = !DILocation(line: 747, column: 5, scope: !1694)
!1703 = !DILocation(line: 748, column: 5, scope: !1694)
!1704 = !DILocation(line: 750, column: 17, scope: !214)
!1705 = !DILocation(line: 750, column: 24, scope: !214)
!1706 = !DILocation(line: 750, column: 10, scope: !214)
!1707 = !DILocation(line: 750, column: 3, scope: !214)
!1708 = !DILocation(line: 751, column: 1, scope: !214)
!1709 = !DILocalVariable(name: "state", arg: 1, scope: !218, file: !1, line: 299, type: !77)
!1710 = !DILocation(line: 299, column: 24, scope: !218)
!1711 = !DILocalVariable(name: "tok", arg: 2, scope: !218, file: !1, line: 300, type: !72)
!1712 = !DILocation(line: 300, column: 14, scope: !218)
!1713 = !DILocalVariable(name: "UNUSED_ptr", arg: 3, scope: !218, file: !1, line: 301, type: !86)
!1714 = !DILocation(line: 301, column: 22, scope: !218)
!1715 = !DILocalVariable(name: "UNUSED_end", arg: 4, scope: !218, file: !1, line: 302, type: !86)
!1716 = !DILocation(line: 302, column: 22, scope: !218)
!1717 = !DILocalVariable(name: "UNUSED_enc", arg: 5, scope: !218, file: !1, line: 303, type: !89)
!1718 = !DILocation(line: 303, column: 26, scope: !218)
!1719 = !DILocation(line: 305, column: 11, scope: !218)
!1720 = !DILocation(line: 305, column: 3, scope: !218)
!1721 = !DILocation(line: 307, column: 5, scope: !1722)
!1722 = distinct !DILexicalBlock(scope: !218, file: !1, line: 305, column: 16)
!1723 = !DILocation(line: 309, column: 5, scope: !1722)
!1724 = !DILocation(line: 309, column: 12, scope: !1722)
!1725 = !DILocation(line: 309, column: 20, scope: !1722)
!1726 = !DILocation(line: 310, column: 5, scope: !1722)
!1727 = !DILocation(line: 312, column: 5, scope: !1722)
!1728 = !DILocation(line: 312, column: 12, scope: !1722)
!1729 = !DILocation(line: 312, column: 20, scope: !1722)
!1730 = !DILocation(line: 313, column: 5, scope: !1722)
!1731 = !DILocation(line: 315, column: 17, scope: !218)
!1732 = !DILocation(line: 315, column: 24, scope: !218)
!1733 = !DILocation(line: 315, column: 10, scope: !218)
!1734 = !DILocation(line: 315, column: 3, scope: !218)
!1735 = !DILocation(line: 316, column: 1, scope: !218)
